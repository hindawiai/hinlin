<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2014 IBM Corp.
 */

#अगर_अघोषित _CXL_H_
#घोषणा _CXL_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/cdev.h>
#समावेश <linux/pid.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/reg.h>
#समावेश <misc/cxl-base.h>

#समावेश <misc/cxl.h>
#समावेश <uapi/misc/cxl.h>

बाह्य uपूर्णांक cxl_verbose;

#घोषणा CXL_TIMEOUT 5

/*
 * Bump version each समय a user API change is made, whether it is
 * backwards compatible ot not.
 */
#घोषणा CXL_API_VERSION 3
#घोषणा CXL_API_VERSION_COMPATIBLE 1

/*
 * Opaque types to aव्योम accidentally passing रेजिस्टरs क्रम the wrong MMIO
 *
 * At the end of the day, I'm not married to using प्रकार here, but it might
 * (and has!) help aव्योम bugs like mixing up CXL_PSL_CtxTime and
 * CXL_PSL_CtxTime_An, or calling cxl_p1n_ग_लिखो instead of cxl_p1_ग_लिखो.
 *
 * I'm quite happy अगर these are changed back to #घोषणाs beक्रमe upstreaming, it
 * should be little more than a regexp search+replace operation in this file.
 */
प्रकार काष्ठा अणु
	स्थिर पूर्णांक x;
पूर्ण cxl_p1_reg_t;
प्रकार काष्ठा अणु
	स्थिर पूर्णांक x;
पूर्ण cxl_p1n_reg_t;
प्रकार काष्ठा अणु
	स्थिर पूर्णांक x;
पूर्ण cxl_p2n_reg_t;
#घोषणा cxl_reg_off(reg) \
	(reg.x)

/* Memory maps. Ref CXL Appendix A */

/* PSL Privilege 1 Memory Map */
/* Configuration and Control area - CAIA 1&2 */
अटल स्थिर cxl_p1_reg_t CXL_PSL_CtxTime = अणु0x0000पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_ErrIVTE = अणु0x0008पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_KEY1    = अणु0x0010पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_KEY2    = अणु0x0018पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_Control = अणु0x0020पूर्ण;
/* Downloading */
अटल स्थिर cxl_p1_reg_t CXL_PSL_DLCNTL  = अणु0x0060पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_DLADDR  = अणु0x0068पूर्ण;

/* PSL Lookaside Buffer Management Area - CAIA 1 */
अटल स्थिर cxl_p1_reg_t CXL_PSL_LBISEL  = अणु0x0080पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_SLBIE   = अणु0x0088पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_SLBIA   = अणु0x0090पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_TLBIE   = अणु0x00A0पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_TLBIA   = अणु0x00A8पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_AFUSEL  = अणु0x00B0पूर्ण;

/* 0x00C0:7EFF Implementation dependent area */
/* PSL रेजिस्टरs - CAIA 1 */
अटल स्थिर cxl_p1_reg_t CXL_PSL_FIR1      = अणु0x0100पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_FIR2      = अणु0x0108पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_Timebase  = अणु0x0110पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_VERSION   = अणु0x0118पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_RESLCKTO  = अणु0x0128पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_TB_CTLSTAT = अणु0x0140पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_FIR_CNTL  = अणु0x0148पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_DSNDCTL   = अणु0x0150पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_SNWRALLOC = अणु0x0158पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL_TRACE     = अणु0x0170पूर्ण;
/* PSL रेजिस्टरs - CAIA 2 */
अटल स्थिर cxl_p1_reg_t CXL_PSL9_CONTROL  = अणु0x0020पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_XSL9_INV      = अणु0x0110पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_XSL9_DBG      = अणु0x0130पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_XSL9_DEF      = अणु0x0140पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_XSL9_DSNCTL   = अणु0x0168पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_FIR1     = अणु0x0300पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_FIR_MASK = अणु0x0308पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_Timebase = अणु0x0310पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_DEBUG    = अणु0x0320पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_FIR_CNTL = अणु0x0348पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_DSNDCTL  = अणु0x0350पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_TB_CTLSTAT = अणु0x0340पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_TRACECFG = अणु0x0368पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_APCDEDALLOC = अणु0x0378पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_APCDEDTYPE = अणु0x0380पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_TNR_ADDR = अणु0x0388पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_CTCCFG = अणु0x0390पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_PSL9_GP_CT = अणु0x0398पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_XSL9_IERAT = अणु0x0588पूर्ण;
अटल स्थिर cxl_p1_reg_t CXL_XSL9_ILPP  = अणु0x0590पूर्ण;

/* 0x7F00:7FFF Reserved PCIe MSI-X Pending Bit Array area */
/* 0x8000:FFFF Reserved PCIe MSI-X Table Area */

/* PSL Slice Privilege 1 Memory Map */
/* Configuration Area - CAIA 1&2 */
अटल स्थिर cxl_p1n_reg_t CXL_PSL_SR_An          = अणु0x00पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_LPID_An        = अणु0x08पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_AMBAR_An       = अणु0x10पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_SPOffset_An    = अणु0x18पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_ID_An          = अणु0x20पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_SERR_An        = अणु0x28पूर्ण;
/* Memory Management and Lookaside Buffer Management - CAIA 1*/
अटल स्थिर cxl_p1n_reg_t CXL_PSL_SDR_An         = अणु0x30पूर्ण;
/* Memory Management and Lookaside Buffer Management - CAIA 1&2 */
अटल स्थिर cxl_p1n_reg_t CXL_PSL_AMOR_An        = अणु0x38पूर्ण;
/* Poपूर्णांकer Area - CAIA 1&2 */
अटल स्थिर cxl_p1n_reg_t CXL_HAURP_An           = अणु0x80पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_SPAP_An        = अणु0x88पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_LLCMD_An       = अणु0x90पूर्ण;
/* Control Area - CAIA 1&2 */
अटल स्थिर cxl_p1n_reg_t CXL_PSL_SCNTL_An       = अणु0xA0पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_CtxTime_An     = अणु0xA8पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_IVTE_Offset_An = अणु0xB0पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_IVTE_Limit_An  = अणु0xB8पूर्ण;
/* 0xC0:FF Implementation Dependent Area - CAIA 1&2 */
अटल स्थिर cxl_p1n_reg_t CXL_PSL_FIR_SLICE_An   = अणु0xC0पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_AFU_DEBUG_An       = अणु0xC8पूर्ण;
/* 0xC0:FF Implementation Dependent Area - CAIA 1 */
अटल स्थिर cxl_p1n_reg_t CXL_PSL_APCALLOC_A     = अणु0xD0पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_COALLOC_A      = अणु0xD8पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_RXCTL_A        = अणु0xE0पूर्ण;
अटल स्थिर cxl_p1n_reg_t CXL_PSL_SLICE_TRACE    = अणु0xE8पूर्ण;

/* PSL Slice Privilege 2 Memory Map */
/* Configuration and Control Area - CAIA 1&2 */
अटल स्थिर cxl_p2n_reg_t CXL_PSL_PID_TID_An = अणु0x000पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_CSRP_An        = अणु0x008पूर्ण;
/* Configuration and Control Area - CAIA 1 */
अटल स्थिर cxl_p2n_reg_t CXL_AURP0_An       = अणु0x010पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_AURP1_An       = अणु0x018पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_SSTP0_An       = अणु0x020पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_SSTP1_An       = अणु0x028पूर्ण;
/* Configuration and Control Area - CAIA 1 */
अटल स्थिर cxl_p2n_reg_t CXL_PSL_AMR_An     = अणु0x030पूर्ण;
/* Segment Lookaside Buffer Management - CAIA 1 */
अटल स्थिर cxl_p2n_reg_t CXL_SLBIE_An       = अणु0x040पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_SLBIA_An       = अणु0x048पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_SLBI_Select_An = अणु0x050पूर्ण;
/* Interrupt Registers - CAIA 1&2 */
अटल स्थिर cxl_p2n_reg_t CXL_PSL_DSISR_An   = अणु0x060पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_PSL_DAR_An     = अणु0x068पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_PSL_DSR_An     = अणु0x070पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_PSL_TFC_An     = अणु0x078पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_PSL_PEHandle_An = अणु0x080पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_PSL_ErrStat_An = अणु0x088पूर्ण;
/* AFU Registers - CAIA 1&2 */
अटल स्थिर cxl_p2n_reg_t CXL_AFU_Cntl_An    = अणु0x090पूर्ण;
अटल स्थिर cxl_p2n_reg_t CXL_AFU_ERR_An     = अणु0x098पूर्ण;
/* Work Element Descriptor - CAIA 1&2 */
अटल स्थिर cxl_p2n_reg_t CXL_PSL_WED_An     = अणु0x0A0पूर्ण;
/* 0x0C0:FFF Implementation Dependent Area */

#घोषणा CXL_PSL_SPAP_Addr 0x0ffffffffffff000ULL
#घोषणा CXL_PSL_SPAP_Size 0x0000000000000ff0ULL
#घोषणा CXL_PSL_SPAP_Size_Shअगरt 4
#घोषणा CXL_PSL_SPAP_V    0x0000000000000001ULL

/****** CXL_PSL_Control ****************************************************/
#घोषणा CXL_PSL_Control_tb              (0x1ull << (63-63))
#घोषणा CXL_PSL_Control_Fr              (0x1ull << (63-31))
#घोषणा CXL_PSL_Control_Fs_MASK         (0x3ull << (63-29))
#घोषणा CXL_PSL_Control_Fs_Complete     (0x3ull << (63-29))

/****** CXL_PSL_DLCNTL *****************************************************/
#घोषणा CXL_PSL_DLCNTL_D (0x1ull << (63-28))
#घोषणा CXL_PSL_DLCNTL_C (0x1ull << (63-29))
#घोषणा CXL_PSL_DLCNTL_E (0x1ull << (63-30))
#घोषणा CXL_PSL_DLCNTL_S (0x1ull << (63-31))
#घोषणा CXL_PSL_DLCNTL_CE (CXL_PSL_DLCNTL_C | CXL_PSL_DLCNTL_E)
#घोषणा CXL_PSL_DLCNTL_DCES (CXL_PSL_DLCNTL_D | CXL_PSL_DLCNTL_CE | CXL_PSL_DLCNTL_S)

/****** CXL_PSL_SR_An ******************************************************/
#घोषणा CXL_PSL_SR_An_SF  MSR_SF            /* 64bit */
#घोषणा CXL_PSL_SR_An_TA  (1ull << (63-1))  /* Tags active,   GA1: 0 */
#घोषणा CXL_PSL_SR_An_HV  MSR_HV            /* Hypervisor,    GA1: 0 */
#घोषणा CXL_PSL_SR_An_XLAT_hpt (0ull << (63-6))/* Hashed page table (HPT) mode */
#घोषणा CXL_PSL_SR_An_XLAT_roh (2ull << (63-6))/* Radix on HPT mode */
#घोषणा CXL_PSL_SR_An_XLAT_ror (3ull << (63-6))/* Radix on Radix mode */
#घोषणा CXL_PSL_SR_An_BOT (1ull << (63-10)) /* Use the in-memory segment table */
#घोषणा CXL_PSL_SR_An_PR  MSR_PR            /* Problem state, GA1: 1 */
#घोषणा CXL_PSL_SR_An_ISL (1ull << (63-53)) /* Ignore Segment Large Page */
#घोषणा CXL_PSL_SR_An_TC  (1ull << (63-54)) /* Page Table secondary hash */
#घोषणा CXL_PSL_SR_An_US  (1ull << (63-56)) /* User state,    GA1: X */
#घोषणा CXL_PSL_SR_An_SC  (1ull << (63-58)) /* Segment Table secondary hash */
#घोषणा CXL_PSL_SR_An_R   MSR_DR            /* Relocate,      GA1: 1 */
#घोषणा CXL_PSL_SR_An_MP  (1ull << (63-62)) /* Master Process */
#घोषणा CXL_PSL_SR_An_LE  (1ull << (63-63)) /* Little Endian */

/****** CXL_PSL_ID_An ****************************************************/
#घोषणा CXL_PSL_ID_An_F	(1ull << (63-31))
#घोषणा CXL_PSL_ID_An_L	(1ull << (63-30))

/****** CXL_PSL_SERR_An ****************************************************/
#घोषणा CXL_PSL_SERR_An_afuto	(1ull << (63-0))
#घोषणा CXL_PSL_SERR_An_afudis	(1ull << (63-1))
#घोषणा CXL_PSL_SERR_An_afuov	(1ull << (63-2))
#घोषणा CXL_PSL_SERR_An_badsrc	(1ull << (63-3))
#घोषणा CXL_PSL_SERR_An_badctx	(1ull << (63-4))
#घोषणा CXL_PSL_SERR_An_llcmdis	(1ull << (63-5))
#घोषणा CXL_PSL_SERR_An_llcmdto	(1ull << (63-6))
#घोषणा CXL_PSL_SERR_An_afupar	(1ull << (63-7))
#घोषणा CXL_PSL_SERR_An_afudup	(1ull << (63-8))
#घोषणा CXL_PSL_SERR_An_IRQS	( \
	CXL_PSL_SERR_An_afuto | CXL_PSL_SERR_An_afudis | CXL_PSL_SERR_An_afuov | \
	CXL_PSL_SERR_An_badsrc | CXL_PSL_SERR_An_badctx | CXL_PSL_SERR_An_llcmdis | \
	CXL_PSL_SERR_An_llcmdto | CXL_PSL_SERR_An_afupar | CXL_PSL_SERR_An_afudup)
#घोषणा CXL_PSL_SERR_An_afuto_mask	(1ull << (63-32))
#घोषणा CXL_PSL_SERR_An_afudis_mask	(1ull << (63-33))
#घोषणा CXL_PSL_SERR_An_afuov_mask	(1ull << (63-34))
#घोषणा CXL_PSL_SERR_An_badsrc_mask	(1ull << (63-35))
#घोषणा CXL_PSL_SERR_An_badctx_mask	(1ull << (63-36))
#घोषणा CXL_PSL_SERR_An_llcmdis_mask	(1ull << (63-37))
#घोषणा CXL_PSL_SERR_An_llcmdto_mask	(1ull << (63-38))
#घोषणा CXL_PSL_SERR_An_afupar_mask	(1ull << (63-39))
#घोषणा CXL_PSL_SERR_An_afudup_mask	(1ull << (63-40))
#घोषणा CXL_PSL_SERR_An_IRQ_MASKS	( \
	CXL_PSL_SERR_An_afuto_mask | CXL_PSL_SERR_An_afudis_mask | CXL_PSL_SERR_An_afuov_mask | \
	CXL_PSL_SERR_An_badsrc_mask | CXL_PSL_SERR_An_badctx_mask | CXL_PSL_SERR_An_llcmdis_mask | \
	CXL_PSL_SERR_An_llcmdto_mask | CXL_PSL_SERR_An_afupar_mask | CXL_PSL_SERR_An_afudup_mask)

#घोषणा CXL_PSL_SERR_An_AE	(1ull << (63-30))

/****** CXL_PSL_SCNTL_An ****************************************************/
#घोषणा CXL_PSL_SCNTL_An_CR          (0x1ull << (63-15))
/* Programming Modes: */
#घोषणा CXL_PSL_SCNTL_An_PM_MASK     (0xffffull << (63-31))
#घोषणा CXL_PSL_SCNTL_An_PM_Shared   (0x0000ull << (63-31))
#घोषणा CXL_PSL_SCNTL_An_PM_OS       (0x0001ull << (63-31))
#घोषणा CXL_PSL_SCNTL_An_PM_Process  (0x0002ull << (63-31))
#घोषणा CXL_PSL_SCNTL_An_PM_AFU      (0x0004ull << (63-31))
#घोषणा CXL_PSL_SCNTL_An_PM_AFU_PBT  (0x0104ull << (63-31))
/* Purge Status (ro) */
#घोषणा CXL_PSL_SCNTL_An_Ps_MASK     (0x3ull << (63-39))
#घोषणा CXL_PSL_SCNTL_An_Ps_Pending  (0x1ull << (63-39))
#घोषणा CXL_PSL_SCNTL_An_Ps_Complete (0x3ull << (63-39))
/* Purge */
#घोषणा CXL_PSL_SCNTL_An_Pc          (0x1ull << (63-48))
/* Suspend Status (ro) */
#घोषणा CXL_PSL_SCNTL_An_Ss_MASK     (0x3ull << (63-55))
#घोषणा CXL_PSL_SCNTL_An_Ss_Pending  (0x1ull << (63-55))
#घोषणा CXL_PSL_SCNTL_An_Ss_Complete (0x3ull << (63-55))
/* Suspend Control */
#घोषणा CXL_PSL_SCNTL_An_Sc          (0x1ull << (63-63))

/* AFU Slice Enable Status (ro) */
#घोषणा CXL_AFU_Cntl_An_ES_MASK     (0x7ull << (63-2))
#घोषणा CXL_AFU_Cntl_An_ES_Disabled (0x0ull << (63-2))
#घोषणा CXL_AFU_Cntl_An_ES_Enabled  (0x4ull << (63-2))
/* AFU Slice Enable */
#घोषणा CXL_AFU_Cntl_An_E           (0x1ull << (63-3))
/* AFU Slice Reset status (ro) */
#घोषणा CXL_AFU_Cntl_An_RS_MASK     (0x3ull << (63-5))
#घोषणा CXL_AFU_Cntl_An_RS_Pending  (0x1ull << (63-5))
#घोषणा CXL_AFU_Cntl_An_RS_Complete (0x2ull << (63-5))
/* AFU Slice Reset */
#घोषणा CXL_AFU_Cntl_An_RA          (0x1ull << (63-7))

/****** CXL_SSTP0/1_An ******************************************************/
/* These top bits are क्रम the segment that CONTAINS the segment table */
#घोषणा CXL_SSTP0_An_B_SHIFT    SLB_VSID_SSIZE_SHIFT
#घोषणा CXL_SSTP0_An_KS             (1ull << (63-2))
#घोषणा CXL_SSTP0_An_KP             (1ull << (63-3))
#घोषणा CXL_SSTP0_An_N              (1ull << (63-4))
#घोषणा CXL_SSTP0_An_L              (1ull << (63-5))
#घोषणा CXL_SSTP0_An_C              (1ull << (63-6))
#घोषणा CXL_SSTP0_An_TA             (1ull << (63-7))
#घोषणा CXL_SSTP0_An_LP_SHIFT                (63-9)  /* 2 Bits */
/* And finally, the भव address & size of the segment table: */
#घोषणा CXL_SSTP0_An_SegTableSize_SHIFT      (63-31) /* 12 Bits */
#घोषणा CXL_SSTP0_An_SegTableSize_MASK \
	(((1ull << 12) - 1) << CXL_SSTP0_An_SegTableSize_SHIFT)
#घोषणा CXL_SSTP0_An_STVA_U_MASK   ((1ull << (63-49))-1)
#घोषणा CXL_SSTP1_An_STVA_L_MASK (~((1ull << (63-55))-1))
#घोषणा CXL_SSTP1_An_V              (1ull << (63-63))

/****** CXL_PSL_SLBIE_[An] - CAIA 1 **************************************************/
/* ग_लिखो: */
#घोषणा CXL_SLBIE_C        PPC_BIT(36)         /* Class */
#घोषणा CXL_SLBIE_SS       PPC_BITMASK(37, 38) /* Segment Size */
#घोषणा CXL_SLBIE_SS_SHIFT PPC_BITLSHIFT(38)
#घोषणा CXL_SLBIE_TA       PPC_BIT(38)         /* Tags Active */
/* पढ़ो: */
#घोषणा CXL_SLBIE_MAX      PPC_BITMASK(24, 31)
#घोषणा CXL_SLBIE_PENDING  PPC_BITMASK(56, 63)

/****** Common to all CXL_TLBIA/SLBIA_[An] - CAIA 1 **********************************/
#घोषणा CXL_TLB_SLB_P          (1ull) /* Pending (पढ़ो) */

/****** Common to all CXL_TLB/SLB_IA/IE_[An] रेजिस्टरs - CAIA 1 **********************/
#घोषणा CXL_TLB_SLB_IQ_ALL     (0ull) /* Inv qualअगरier */
#घोषणा CXL_TLB_SLB_IQ_LPID    (1ull) /* Inv qualअगरier */
#घोषणा CXL_TLB_SLB_IQ_LPIDPID (3ull) /* Inv qualअगरier */

/****** CXL_PSL_AFUSEL ******************************************************/
#घोषणा CXL_PSL_AFUSEL_A (1ull << (63-55)) /* Adapter wide invalidates affect all AFUs */

/****** CXL_PSL_DSISR_An - CAIA 1 ****************************************************/
#घोषणा CXL_PSL_DSISR_An_DS (1ull << (63-0))  /* Segment not found */
#घोषणा CXL_PSL_DSISR_An_DM (1ull << (63-1))  /* PTE not found (See also: M) or protection fault */
#घोषणा CXL_PSL_DSISR_An_ST (1ull << (63-2))  /* Segment Table PTE not found */
#घोषणा CXL_PSL_DSISR_An_UR (1ull << (63-3))  /* AURP PTE not found */
#घोषणा CXL_PSL_DSISR_TRANS (CXL_PSL_DSISR_An_DS | CXL_PSL_DSISR_An_DM | CXL_PSL_DSISR_An_ST | CXL_PSL_DSISR_An_UR)
#घोषणा CXL_PSL_DSISR_An_PE (1ull << (63-4))  /* PSL Error (implementation specअगरic) */
#घोषणा CXL_PSL_DSISR_An_AE (1ull << (63-5))  /* AFU Error */
#घोषणा CXL_PSL_DSISR_An_OC (1ull << (63-6))  /* OS Context Warning */
#घोषणा CXL_PSL_DSISR_PENDING (CXL_PSL_DSISR_TRANS | CXL_PSL_DSISR_An_PE | CXL_PSL_DSISR_An_AE | CXL_PSL_DSISR_An_OC)
/* NOTE: Bits 32:63 are undefined अगर DSISR[DS] = 1 */
#घोषणा CXL_PSL_DSISR_An_M  DSISR_NOHPTE      /* PTE not found */
#घोषणा CXL_PSL_DSISR_An_P  DSISR_PROTFAULT   /* Storage protection violation */
#घोषणा CXL_PSL_DSISR_An_A  (1ull << (63-37)) /* AFU lock access to ग_लिखो through or cache inhibited storage */
#घोषणा CXL_PSL_DSISR_An_S  DSISR_ISSTORE     /* Access was afu_wr or afu_zero */
#घोषणा CXL_PSL_DSISR_An_K  DSISR_KEYFAULT    /* Access not permitted by भव page class key protection */

/****** CXL_PSL_DSISR_An - CAIA 2 ****************************************************/
#घोषणा CXL_PSL9_DSISR_An_TF (1ull << (63-3))  /* Translation fault */
#घोषणा CXL_PSL9_DSISR_An_PE (1ull << (63-4))  /* PSL Error (implementation specअगरic) */
#घोषणा CXL_PSL9_DSISR_An_AE (1ull << (63-5))  /* AFU Error */
#घोषणा CXL_PSL9_DSISR_An_OC (1ull << (63-6))  /* OS Context Warning */
#घोषणा CXL_PSL9_DSISR_An_S (1ull << (63-38))  /* TF क्रम a ग_लिखो operation */
#घोषणा CXL_PSL9_DSISR_PENDING (CXL_PSL9_DSISR_An_TF | CXL_PSL9_DSISR_An_PE | CXL_PSL9_DSISR_An_AE | CXL_PSL9_DSISR_An_OC)
/*
 * NOTE: Bits 56:63 (Checkout Response Status) are valid when DSISR_An[TF] = 1
 * Status (0:7) Encoding
 */
#घोषणा CXL_PSL9_DSISR_An_CO_MASK 0x00000000000000ffULL
#घोषणा CXL_PSL9_DSISR_An_SF      0x0000000000000080ULL  /* Segment Fault                        0b10000000 */
#घोषणा CXL_PSL9_DSISR_An_PF_SLR  0x0000000000000088ULL  /* PTE not found (Single Level Radix)   0b10001000 */
#घोषणा CXL_PSL9_DSISR_An_PF_RGC  0x000000000000008CULL  /* PTE not found (Radix Guest (child))  0b10001100 */
#घोषणा CXL_PSL9_DSISR_An_PF_RGP  0x0000000000000090ULL  /* PTE not found (Radix Guest (parent)) 0b10010000 */
#घोषणा CXL_PSL9_DSISR_An_PF_HRH  0x0000000000000094ULL  /* PTE not found (HPT/Radix Host)       0b10010100 */
#घोषणा CXL_PSL9_DSISR_An_PF_STEG 0x000000000000009CULL  /* PTE not found (STEG VA)              0b10011100 */
#घोषणा CXL_PSL9_DSISR_An_URTCH   0x00000000000000B4ULL  /* Unsupported Radix Tree Configuration 0b10110100 */

/****** CXL_PSL_TFC_An ******************************************************/
#घोषणा CXL_PSL_TFC_An_A  (1ull << (63-28)) /* Acknowledge non-translation fault */
#घोषणा CXL_PSL_TFC_An_C  (1ull << (63-29)) /* Continue (पात transaction) */
#घोषणा CXL_PSL_TFC_An_AE (1ull << (63-30)) /* Restart PSL with address error */
#घोषणा CXL_PSL_TFC_An_R  (1ull << (63-31)) /* Restart PSL transaction */

/****** CXL_PSL_DEBUG *****************************************************/
#घोषणा CXL_PSL_DEBUG_CDC  (1ull << (63-27)) /* Coherent Data cache support */

/****** CXL_XSL9_IERAT_ERAT - CAIA 2 **********************************/
#घोषणा CXL_XSL9_IERAT_MLPID    (1ull << (63-0))  /* Match LPID */
#घोषणा CXL_XSL9_IERAT_MPID     (1ull << (63-1))  /* Match PID */
#घोषणा CXL_XSL9_IERAT_PRS      (1ull << (63-4))  /* PRS bit क्रम Radix invalidations */
#घोषणा CXL_XSL9_IERAT_INVR     (1ull << (63-3))  /* Invalidate Radix */
#घोषणा CXL_XSL9_IERAT_IALL     (1ull << (63-8))  /* Invalidate All */
#घोषणा CXL_XSL9_IERAT_IINPROG  (1ull << (63-63)) /* Invalidate in progress */

/* cxl_process_element->software_status */
#घोषणा CXL_PE_SOFTWARE_STATE_V (1ul << (31 -  0)) /* Valid */
#घोषणा CXL_PE_SOFTWARE_STATE_C (1ul << (31 - 29)) /* Complete */
#घोषणा CXL_PE_SOFTWARE_STATE_S (1ul << (31 - 30)) /* Suspend */
#घोषणा CXL_PE_SOFTWARE_STATE_T (1ul << (31 - 31)) /* Terminate */

/****** CXL_PSL_RXCTL_An (Implementation Specअगरic) **************************
 * Controls AFU Hang Pulse, which sets the समयout क्रम the AFU to respond to
 * the PSL क्रम any response (except MMIO). Timeouts will occur between 1x to 2x
 * of the hang pulse frequency.
 */
#घोषणा CXL_PSL_RXCTL_AFUHP_4S      0x7000000000000000ULL

/* SPA->sw_command_status */
#घोषणा CXL_SPA_SW_CMD_MASK         0xffff000000000000ULL
#घोषणा CXL_SPA_SW_CMD_TERMINATE    0x0001000000000000ULL
#घोषणा CXL_SPA_SW_CMD_REMOVE       0x0002000000000000ULL
#घोषणा CXL_SPA_SW_CMD_SUSPEND      0x0003000000000000ULL
#घोषणा CXL_SPA_SW_CMD_RESUME       0x0004000000000000ULL
#घोषणा CXL_SPA_SW_CMD_ADD          0x0005000000000000ULL
#घोषणा CXL_SPA_SW_CMD_UPDATE       0x0006000000000000ULL
#घोषणा CXL_SPA_SW_STATE_MASK       0x0000ffff00000000ULL
#घोषणा CXL_SPA_SW_STATE_TERMINATED 0x0000000100000000ULL
#घोषणा CXL_SPA_SW_STATE_REMOVED    0x0000000200000000ULL
#घोषणा CXL_SPA_SW_STATE_SUSPENDED  0x0000000300000000ULL
#घोषणा CXL_SPA_SW_STATE_RESUMED    0x0000000400000000ULL
#घोषणा CXL_SPA_SW_STATE_ADDED      0x0000000500000000ULL
#घोषणा CXL_SPA_SW_STATE_UPDATED    0x0000000600000000ULL
#घोषणा CXL_SPA_SW_PSL_ID_MASK      0x00000000ffff0000ULL
#घोषणा CXL_SPA_SW_LINK_MASK        0x000000000000ffffULL

#घोषणा CXL_MAX_SLICES 4
#घोषणा MAX_AFU_MMIO_REGS 3

#घोषणा CXL_MODE_TIME_SLICED 0x4
#घोषणा CXL_SUPPORTED_MODES (CXL_MODE_DEDICATED | CXL_MODE_सूचीECTED)

#घोषणा CXL_DEV_MINORS 13   /* 1 control + 4 AFUs * 3 (dedicated/master/shared) */
#घोषणा CXL_CARD_MINOR(adapter) (adapter->adapter_num * CXL_DEV_MINORS)
#घोषणा CXL_DEVT_ADAPTER(dev) (MINOR(dev) / CXL_DEV_MINORS)

#घोषणा CXL_PSL9_TRACEID_MAX 0xAU
#घोषणा CXL_PSL9_TRACESTATE_FIN 0x3U

क्रमागत cxl_context_status अणु
	CLOSED,
	OPENED,
	STARTED
पूर्ण;

क्रमागत prefault_modes अणु
	CXL_PREFAULT_NONE,
	CXL_PREFAULT_WED,
	CXL_PREFAULT_ALL,
पूर्ण;

क्रमागत cxl_attrs अणु
	CXL_ADAPTER_ATTRS,
	CXL_AFU_MASTER_ATTRS,
	CXL_AFU_ATTRS,
पूर्ण;

काष्ठा cxl_sste अणु
	__be64 esid_data;
	__be64 vsid_data;
पूर्ण;

#घोषणा to_cxl_adapter(d) container_of(d, काष्ठा cxl, dev)
#घोषणा to_cxl_afu(d) container_of(d, काष्ठा cxl_afu, dev)

काष्ठा cxl_afu_native अणु
	व्योम __iomem *p1n_mmio;
	व्योम __iomem *afu_desc_mmio;
	irq_hw_number_t psl_hwirq;
	अचिन्हित पूर्णांक psl_virq;
	काष्ठा mutex spa_mutex;
	/*
	 * Only the first part of the SPA is used क्रम the process element
	 * linked list. The only other part that software needs to worry about
	 * is sw_command_status, which we store a separate poपूर्णांकer to.
	 * Everything अन्यथा in the SPA is only used by hardware
	 */
	काष्ठा cxl_process_element *spa;
	__be64 *sw_command_status;
	अचिन्हित पूर्णांक spa_size;
	पूर्णांक spa_order;
	पूर्णांक spa_max_procs;
	u64 pp_offset;
पूर्ण;

काष्ठा cxl_afu_guest अणु
	काष्ठा cxl_afu *parent;
	u64 handle;
	phys_addr_t p2n_phys;
	u64 p2n_size;
	पूर्णांक max_पूर्णांकs;
	bool handle_err;
	काष्ठा delayed_work work_err;
	पूर्णांक previous_state;
पूर्ण;

काष्ठा cxl_afu अणु
	काष्ठा cxl_afu_native *native;
	काष्ठा cxl_afu_guest *guest;
	irq_hw_number_t serr_hwirq;
	अचिन्हित पूर्णांक serr_virq;
	अक्षर *psl_irq_name;
	अक्षर *err_irq_name;
	व्योम __iomem *p2n_mmio;
	phys_addr_t psn_phys;
	u64 pp_size;

	काष्ठा cxl *adapter;
	काष्ठा device dev;
	काष्ठा cdev afu_cdev_s, afu_cdev_m, afu_cdev_d;
	काष्ठा device *अक्षरdev_s, *अक्षरdev_m, *अक्षरdev_d;
	काष्ठा idr contexts_idr;
	काष्ठा dentry *debugfs;
	काष्ठा mutex contexts_lock;
	spinlock_t afu_cntl_lock;

	/* -1: AFU deconfigured/locked, >= 0: number of पढ़ोers */
	atomic_t configured_state;

	/* AFU error buffer fields and bin attribute क्रम sysfs */
	u64 eb_len, eb_offset;
	काष्ठा bin_attribute attr_eb;

	/* poपूर्णांकer to the vphb */
	काष्ठा pci_controller *phb;

	पूर्णांक pp_irqs;
	पूर्णांक irqs_max;
	पूर्णांक num_procs;
	पूर्णांक max_procs_भवised;
	पूर्णांक slice;
	पूर्णांक modes_supported;
	पूर्णांक current_mode;
	पूर्णांक crs_num;
	u64 crs_len;
	u64 crs_offset;
	काष्ठा list_head crs;
	क्रमागत prefault_modes prefault_mode;
	bool psa;
	bool pp_psa;
	bool enabled;
पूर्ण;


काष्ठा cxl_irq_name अणु
	काष्ठा list_head list;
	अक्षर *name;
पूर्ण;

काष्ठा irq_avail अणु
	irq_hw_number_t offset;
	irq_hw_number_t range;
	अचिन्हित दीर्घ   *biपंचांगap;
पूर्ण;

/*
 * This is a cxl context.  If the PSL is in dedicated mode, there will be one
 * of these per AFU.  If in AFU directed there can be lots of these.
 */
काष्ठा cxl_context अणु
	काष्ठा cxl_afu *afu;

	/* Problem state MMIO */
	phys_addr_t psn_phys;
	u64 psn_size;

	/* Used to unmap any mmaps when क्रमce detaching */
	काष्ठा address_space *mapping;
	काष्ठा mutex mapping_lock;
	काष्ठा page *ff_page;
	bool mmio_err_ff;
	bool kernelapi;

	spinlock_t sste_lock; /* Protects segment table entries */
	काष्ठा cxl_sste *sstp;
	u64 sstp0, sstp1;
	अचिन्हित पूर्णांक sst_size, sst_lru;

	रुको_queue_head_t wq;
	/* use mm context associated with this pid क्रम ds faults */
	काष्ठा pid *pid;
	spinlock_t lock; /* Protects pending_irq_mask, pending_fault and fault_addr */
	/* Only used in PR mode */
	u64 process_token;

	/* driver निजी data */
	व्योम *priv;

	अचिन्हित दीर्घ *irq_biपंचांगap; /* Accessed from IRQ context */
	काष्ठा cxl_irq_ranges irqs;
	काष्ठा list_head irq_names;
	u64 fault_addr;
	u64 fault_dsisr;
	u64 afu_err;

	/*
	 * This status and it's lock pretects start and detach context
	 * from racing.  It also prevents detach from racing with
	 * itself
	 */
	क्रमागत cxl_context_status status;
	काष्ठा mutex status_mutex;


	/* XXX: Is it possible to need multiple work items at once? */
	काष्ठा work_काष्ठा fault_work;
	u64 dsisr;
	u64 dar;

	काष्ठा cxl_process_element *elem;

	/*
	 * pe is the process element handle, asचिन्हित by this driver when the
	 * context is initialized.
	 *
	 * बाह्यal_pe is the PE shown outside of cxl.
	 * On bare-metal, pe=बाह्यal_pe, because we decide what the handle is.
	 * In a guest, we only find out about the pe used by pHyp when the
	 * context is attached, and that's the value we want to report outside
	 * of cxl.
	 */
	पूर्णांक pe;
	पूर्णांक बाह्यal_pe;

	u32 irq_count;
	bool pe_inserted;
	bool master;
	bool kernel;
	bool pending_irq;
	bool pending_fault;
	bool pending_afu_err;

	/* Used by AFU drivers क्रम driver specअगरic event delivery */
	काष्ठा cxl_afu_driver_ops *afu_driver_ops;
	atomic_t afu_driver_events;

	काष्ठा rcu_head rcu;

	काष्ठा mm_काष्ठा *mm;

	u16 tidr;
	bool assign_tidr;
पूर्ण;

काष्ठा cxl_irq_info;

काष्ठा cxl_service_layer_ops अणु
	पूर्णांक (*adapter_regs_init)(काष्ठा cxl *adapter, काष्ठा pci_dev *dev);
	पूर्णांक (*invalidate_all)(काष्ठा cxl *adapter);
	पूर्णांक (*afu_regs_init)(काष्ठा cxl_afu *afu);
	पूर्णांक (*sanitise_afu_regs)(काष्ठा cxl_afu *afu);
	पूर्णांक (*रेजिस्टर_serr_irq)(काष्ठा cxl_afu *afu);
	व्योम (*release_serr_irq)(काष्ठा cxl_afu *afu);
	irqवापस_t (*handle_पूर्णांकerrupt)(पूर्णांक irq, काष्ठा cxl_context *ctx, काष्ठा cxl_irq_info *irq_info);
	irqवापस_t (*fail_irq)(काष्ठा cxl_afu *afu, काष्ठा cxl_irq_info *irq_info);
	पूर्णांक (*activate_dedicated_process)(काष्ठा cxl_afu *afu);
	पूर्णांक (*attach_afu_directed)(काष्ठा cxl_context *ctx, u64 wed, u64 amr);
	पूर्णांक (*attach_dedicated_process)(काष्ठा cxl_context *ctx, u64 wed, u64 amr);
	व्योम (*update_dedicated_ivtes)(काष्ठा cxl_context *ctx);
	व्योम (*debugfs_add_adapter_regs)(काष्ठा cxl *adapter, काष्ठा dentry *dir);
	व्योम (*debugfs_add_afu_regs)(काष्ठा cxl_afu *afu, काष्ठा dentry *dir);
	व्योम (*psl_irq_dump_रेजिस्टरs)(काष्ठा cxl_context *ctx);
	व्योम (*err_irq_dump_रेजिस्टरs)(काष्ठा cxl *adapter);
	व्योम (*debugfs_stop_trace)(काष्ठा cxl *adapter);
	व्योम (*ग_लिखो_समयbase_ctrl)(काष्ठा cxl *adapter);
	u64 (*समयbase_पढ़ो)(काष्ठा cxl *adapter);
	पूर्णांक capi_mode;
	bool needs_reset_beक्रमe_disable;
पूर्ण;

काष्ठा cxl_native अणु
	u64 afu_desc_off;
	u64 afu_desc_size;
	व्योम __iomem *p1_mmio;
	व्योम __iomem *p2_mmio;
	irq_hw_number_t err_hwirq;
	अचिन्हित पूर्णांक err_virq;
	u64 ps_off;
	bool no_data_cache; /* set अगर no data cache on the card */
	स्थिर काष्ठा cxl_service_layer_ops *sl_ops;
पूर्ण;

काष्ठा cxl_guest अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक irq_nranges;
	काष्ठा cdev cdev;
	irq_hw_number_t irq_base_offset;
	काष्ठा irq_avail *irq_avail;
	spinlock_t irq_alloc_lock;
	u64 handle;
	अक्षर *status;
	u16 venकरोr;
	u16 device;
	u16 subप्रणाली_venकरोr;
	u16 subप्रणाली;
पूर्ण;

काष्ठा cxl अणु
	काष्ठा cxl_native *native;
	काष्ठा cxl_guest *guest;
	spinlock_t afu_list_lock;
	काष्ठा cxl_afu *afu[CXL_MAX_SLICES];
	काष्ठा device dev;
	काष्ठा dentry *trace;
	काष्ठा dentry *psl_err_chk;
	काष्ठा dentry *debugfs;
	अक्षर *irq_name;
	काष्ठा bin_attribute cxl_attr;
	पूर्णांक adapter_num;
	पूर्णांक user_irqs;
	u64 ps_size;
	u16 psl_rev;
	u16 base_image;
	u8 vsec_status;
	u8 caia_major;
	u8 caia_minor;
	u8 slices;
	bool user_image_loaded;
	bool perst_loads_image;
	bool perst_select_user;
	bool perst_same_image;
	bool psl_समयbase_synced;
	bool tunneled_ops_supported;

	/*
	 * number of contexts mapped on to this card. Possible values are:
	 * >0: Number of contexts mapped and new one can be mapped.
	 *  0: No active contexts and new ones can be mapped.
	 * -1: No contexts mapped and new ones cannot be mapped.
	 */
	atomic_t contexts_num;
पूर्ण;

पूर्णांक cxl_pci_alloc_one_irq(काष्ठा cxl *adapter);
व्योम cxl_pci_release_one_irq(काष्ठा cxl *adapter, पूर्णांक hwirq);
पूर्णांक cxl_pci_alloc_irq_ranges(काष्ठा cxl_irq_ranges *irqs, काष्ठा cxl *adapter, अचिन्हित पूर्णांक num);
व्योम cxl_pci_release_irq_ranges(काष्ठा cxl_irq_ranges *irqs, काष्ठा cxl *adapter);
पूर्णांक cxl_pci_setup_irq(काष्ठा cxl *adapter, अचिन्हित पूर्णांक hwirq, अचिन्हित पूर्णांक virq);
पूर्णांक cxl_update_image_control(काष्ठा cxl *adapter);
पूर्णांक cxl_pci_reset(काष्ठा cxl *adapter);
व्योम cxl_pci_release_afu(काष्ठा device *dev);
sमाप_प्रकार cxl_pci_पढ़ो_adapter_vpd(काष्ठा cxl *adapter, व्योम *buf, माप_प्रकार len);

/* common == phyp + घातernv - CAIA 1&2 */
काष्ठा cxl_process_element_common अणु
	__be32 tid;
	__be32 pid;
	__be64 csrp;
	जोड़ अणु
		काष्ठा अणु
			__be64 aurp0;
			__be64 aurp1;
			__be64 sstp0;
			__be64 sstp1;
		पूर्ण psl8;  /* CAIA 1 */
		काष्ठा अणु
			u8     reserved2[8];
			u8     reserved3[8];
			u8     reserved4[8];
			u8     reserved5[8];
		पूर्ण psl9;  /* CAIA 2 */
	पूर्ण u;
	__be64 amr;
	u8     reserved6[4];
	__be64 wed;
पूर्ण __packed;

/* just घातernv - CAIA 1&2 */
काष्ठा cxl_process_element अणु
	__be64 sr;
	__be64 SPOffset;
	जोड़ अणु
		__be64 sdr;          /* CAIA 1 */
		u8     reserved1[8]; /* CAIA 2 */
	पूर्ण u;
	__be64 haurp;
	__be32 ctxसमय;
	__be16 ivte_offsets[4];
	__be16 ivte_ranges[4];
	__be32 lpid;
	काष्ठा cxl_process_element_common common;
	__be32 software_state;
पूर्ण __packed;

अटल अंतरभूत bool cxl_adapter_link_ok(काष्ठा cxl *cxl, काष्ठा cxl_afu *afu)
अणु
	काष्ठा pci_dev *pdev;

	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		pdev = to_pci_dev(cxl->dev.parent);
		वापस !pci_channel_offline(pdev);
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत व्योम __iomem *_cxl_p1_addr(काष्ठा cxl *cxl, cxl_p1_reg_t reg)
अणु
	WARN_ON(!cpu_has_feature(CPU_FTR_HVMODE));
	वापस cxl->native->p1_mmio + cxl_reg_off(reg);
पूर्ण

अटल अंतरभूत व्योम cxl_p1_ग_लिखो(काष्ठा cxl *cxl, cxl_p1_reg_t reg, u64 val)
अणु
	अगर (likely(cxl_adapter_link_ok(cxl, शून्य)))
		out_be64(_cxl_p1_addr(cxl, reg), val);
पूर्ण

अटल अंतरभूत u64 cxl_p1_पढ़ो(काष्ठा cxl *cxl, cxl_p1_reg_t reg)
अणु
	अगर (likely(cxl_adapter_link_ok(cxl, शून्य)))
		वापस in_be64(_cxl_p1_addr(cxl, reg));
	अन्यथा
		वापस ~0ULL;
पूर्ण

अटल अंतरभूत व्योम __iomem *_cxl_p1n_addr(काष्ठा cxl_afu *afu, cxl_p1n_reg_t reg)
अणु
	WARN_ON(!cpu_has_feature(CPU_FTR_HVMODE));
	वापस afu->native->p1n_mmio + cxl_reg_off(reg);
पूर्ण

अटल अंतरभूत व्योम cxl_p1n_ग_लिखो(काष्ठा cxl_afu *afu, cxl_p1n_reg_t reg, u64 val)
अणु
	अगर (likely(cxl_adapter_link_ok(afu->adapter, afu)))
		out_be64(_cxl_p1n_addr(afu, reg), val);
पूर्ण

अटल अंतरभूत u64 cxl_p1n_पढ़ो(काष्ठा cxl_afu *afu, cxl_p1n_reg_t reg)
अणु
	अगर (likely(cxl_adapter_link_ok(afu->adapter, afu)))
		वापस in_be64(_cxl_p1n_addr(afu, reg));
	अन्यथा
		वापस ~0ULL;
पूर्ण

अटल अंतरभूत व्योम __iomem *_cxl_p2n_addr(काष्ठा cxl_afu *afu, cxl_p2n_reg_t reg)
अणु
	वापस afu->p2n_mmio + cxl_reg_off(reg);
पूर्ण

अटल अंतरभूत व्योम cxl_p2n_ग_लिखो(काष्ठा cxl_afu *afu, cxl_p2n_reg_t reg, u64 val)
अणु
	अगर (likely(cxl_adapter_link_ok(afu->adapter, afu)))
		out_be64(_cxl_p2n_addr(afu, reg), val);
पूर्ण

अटल अंतरभूत u64 cxl_p2n_पढ़ो(काष्ठा cxl_afu *afu, cxl_p2n_reg_t reg)
अणु
	अगर (likely(cxl_adapter_link_ok(afu->adapter, afu)))
		वापस in_be64(_cxl_p2n_addr(afu, reg));
	अन्यथा
		वापस ~0ULL;
पूर्ण

अटल अंतरभूत bool cxl_is_घातer8(व्योम)
अणु
	अगर ((pvr_version_is(PVR_POWER8E)) ||
	    (pvr_version_is(PVR_POWER8NVL)) ||
	    (pvr_version_is(PVR_POWER8)))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool cxl_is_घातer9(व्योम)
अणु
	अगर (pvr_version_is(PVR_POWER9))
		वापस true;
	वापस false;
पूर्ण

sमाप_प्रकार cxl_pci_afu_पढ़ो_err_buffer(काष्ठा cxl_afu *afu, अक्षर *buf,
				loff_t off, माप_प्रकार count);


काष्ठा cxl_calls अणु
	व्योम (*cxl_slbia)(काष्ठा mm_काष्ठा *mm);
	काष्ठा module *owner;
पूर्ण;
पूर्णांक रेजिस्टर_cxl_calls(काष्ठा cxl_calls *calls);
व्योम unरेजिस्टर_cxl_calls(काष्ठा cxl_calls *calls);
पूर्णांक cxl_update_properties(काष्ठा device_node *dn, काष्ठा property *new_prop);

व्योम cxl_हटाओ_adapter_nr(काष्ठा cxl *adapter);

व्योम cxl_release_spa(काष्ठा cxl_afu *afu);

dev_t cxl_get_dev(व्योम);
पूर्णांक cxl_file_init(व्योम);
व्योम cxl_file_निकास(व्योम);
पूर्णांक cxl_रेजिस्टर_adapter(काष्ठा cxl *adapter);
पूर्णांक cxl_रेजिस्टर_afu(काष्ठा cxl_afu *afu);
पूर्णांक cxl_अक्षरdev_d_afu_add(काष्ठा cxl_afu *afu);
पूर्णांक cxl_अक्षरdev_m_afu_add(काष्ठा cxl_afu *afu);
पूर्णांक cxl_अक्षरdev_s_afu_add(काष्ठा cxl_afu *afu);
व्योम cxl_अक्षरdev_afu_हटाओ(काष्ठा cxl_afu *afu);

व्योम cxl_context_detach_all(काष्ठा cxl_afu *afu);
व्योम cxl_context_मुक्त(काष्ठा cxl_context *ctx);
व्योम cxl_context_detach(काष्ठा cxl_context *ctx);

पूर्णांक cxl_sysfs_adapter_add(काष्ठा cxl *adapter);
व्योम cxl_sysfs_adapter_हटाओ(काष्ठा cxl *adapter);
पूर्णांक cxl_sysfs_afu_add(काष्ठा cxl_afu *afu);
व्योम cxl_sysfs_afu_हटाओ(काष्ठा cxl_afu *afu);
पूर्णांक cxl_sysfs_afu_m_add(काष्ठा cxl_afu *afu);
व्योम cxl_sysfs_afu_m_हटाओ(काष्ठा cxl_afu *afu);

काष्ठा cxl *cxl_alloc_adapter(व्योम);
काष्ठा cxl_afu *cxl_alloc_afu(काष्ठा cxl *adapter, पूर्णांक slice);
पूर्णांक cxl_afu_select_best_mode(काष्ठा cxl_afu *afu);

पूर्णांक cxl_native_रेजिस्टर_psl_irq(काष्ठा cxl_afu *afu);
व्योम cxl_native_release_psl_irq(काष्ठा cxl_afu *afu);
पूर्णांक cxl_native_रेजिस्टर_psl_err_irq(काष्ठा cxl *adapter);
व्योम cxl_native_release_psl_err_irq(काष्ठा cxl *adapter);
पूर्णांक cxl_native_रेजिस्टर_serr_irq(काष्ठा cxl_afu *afu);
व्योम cxl_native_release_serr_irq(काष्ठा cxl_afu *afu);
पूर्णांक afu_रेजिस्टर_irqs(काष्ठा cxl_context *ctx, u32 count);
व्योम afu_release_irqs(काष्ठा cxl_context *ctx, व्योम *cookie);
व्योम afu_irq_name_मुक्त(काष्ठा cxl_context *ctx);

पूर्णांक cxl_attach_afu_directed_psl9(काष्ठा cxl_context *ctx, u64 wed, u64 amr);
पूर्णांक cxl_attach_afu_directed_psl8(काष्ठा cxl_context *ctx, u64 wed, u64 amr);
पूर्णांक cxl_activate_dedicated_process_psl9(काष्ठा cxl_afu *afu);
पूर्णांक cxl_activate_dedicated_process_psl8(काष्ठा cxl_afu *afu);
पूर्णांक cxl_attach_dedicated_process_psl9(काष्ठा cxl_context *ctx, u64 wed, u64 amr);
पूर्णांक cxl_attach_dedicated_process_psl8(काष्ठा cxl_context *ctx, u64 wed, u64 amr);
व्योम cxl_update_dedicated_ivtes_psl9(काष्ठा cxl_context *ctx);
व्योम cxl_update_dedicated_ivtes_psl8(काष्ठा cxl_context *ctx);

#अगर_घोषित CONFIG_DEBUG_FS

व्योम cxl_debugfs_init(व्योम);
व्योम cxl_debugfs_निकास(व्योम);
व्योम cxl_debugfs_adapter_add(काष्ठा cxl *adapter);
व्योम cxl_debugfs_adapter_हटाओ(काष्ठा cxl *adapter);
व्योम cxl_debugfs_afu_add(काष्ठा cxl_afu *afu);
व्योम cxl_debugfs_afu_हटाओ(काष्ठा cxl_afu *afu);
व्योम cxl_debugfs_add_adapter_regs_psl9(काष्ठा cxl *adapter, काष्ठा dentry *dir);
व्योम cxl_debugfs_add_adapter_regs_psl8(काष्ठा cxl *adapter, काष्ठा dentry *dir);
व्योम cxl_debugfs_add_afu_regs_psl9(काष्ठा cxl_afu *afu, काष्ठा dentry *dir);
व्योम cxl_debugfs_add_afu_regs_psl8(काष्ठा cxl_afu *afu, काष्ठा dentry *dir);

#अन्यथा /* CONFIG_DEBUG_FS */

अटल अंतरभूत व्योम __init cxl_debugfs_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_निकास(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_adapter_add(काष्ठा cxl *adapter)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_adapter_हटाओ(काष्ठा cxl *adapter)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_afu_add(काष्ठा cxl_afu *afu)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_afu_हटाओ(काष्ठा cxl_afu *afu)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_add_adapter_regs_psl9(काष्ठा cxl *adapter,
						    काष्ठा dentry *dir)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_add_adapter_regs_psl8(काष्ठा cxl *adapter,
						    काष्ठा dentry *dir)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_add_afu_regs_psl9(काष्ठा cxl_afu *afu, काष्ठा dentry *dir)
अणु
पूर्ण

अटल अंतरभूत व्योम cxl_debugfs_add_afu_regs_psl8(काष्ठा cxl_afu *afu, काष्ठा dentry *dir)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

व्योम cxl_handle_fault(काष्ठा work_काष्ठा *work);
व्योम cxl_prefault(काष्ठा cxl_context *ctx, u64 wed);
पूर्णांक cxl_handle_mm_fault(काष्ठा mm_काष्ठा *mm, u64 dsisr, u64 dar);

काष्ठा cxl *get_cxl_adapter(पूर्णांक num);
पूर्णांक cxl_alloc_sst(काष्ठा cxl_context *ctx);
व्योम cxl_dump_debug_buffer(व्योम *addr, माप_प्रकार size);

व्योम init_cxl_native(व्योम);

काष्ठा cxl_context *cxl_context_alloc(व्योम);
पूर्णांक cxl_context_init(काष्ठा cxl_context *ctx, काष्ठा cxl_afu *afu, bool master);
व्योम cxl_context_set_mapping(काष्ठा cxl_context *ctx,
			काष्ठा address_space *mapping);
व्योम cxl_context_मुक्त(काष्ठा cxl_context *ctx);
पूर्णांक cxl_context_iomap(काष्ठा cxl_context *ctx, काष्ठा vm_area_काष्ठा *vma);
अचिन्हित पूर्णांक cxl_map_irq(काष्ठा cxl *adapter, irq_hw_number_t hwirq,
			 irq_handler_t handler, व्योम *cookie, स्थिर अक्षर *name);
व्योम cxl_unmap_irq(अचिन्हित पूर्णांक virq, व्योम *cookie);
पूर्णांक __detach_context(काष्ठा cxl_context *ctx);

/*
 * This must match the layout of the H_COLLECT_CA_INT_INFO retbuf defined
 * in PAPR.
 * Field pid_tid is now 'reserved' because it's no more used on bare-metal.
 * On a guest environment, PSL_PID_An is located on the upper 32 bits and
 * PSL_TID_An रेजिस्टर in the lower 32 bits.
 */
काष्ठा cxl_irq_info अणु
	u64 dsisr;
	u64 dar;
	u64 dsr;
	u64 reserved;
	u64 afu_err;
	u64 errstat;
	u64 proc_handle;
	u64 padding[2]; /* to match the expected retbuf size क्रम plpar_hcall9 */
पूर्ण;

व्योम cxl_assign_psn_space(काष्ठा cxl_context *ctx);
पूर्णांक cxl_invalidate_all_psl9(काष्ठा cxl *adapter);
पूर्णांक cxl_invalidate_all_psl8(काष्ठा cxl *adapter);
irqवापस_t cxl_irq_psl9(पूर्णांक irq, काष्ठा cxl_context *ctx, काष्ठा cxl_irq_info *irq_info);
irqवापस_t cxl_irq_psl8(पूर्णांक irq, काष्ठा cxl_context *ctx, काष्ठा cxl_irq_info *irq_info);
irqवापस_t cxl_fail_irq_psl(काष्ठा cxl_afu *afu, काष्ठा cxl_irq_info *irq_info);
पूर्णांक cxl_रेजिस्टर_one_irq(काष्ठा cxl *adapter, irq_handler_t handler,
			व्योम *cookie, irq_hw_number_t *dest_hwirq,
			अचिन्हित पूर्णांक *dest_virq, स्थिर अक्षर *name);

पूर्णांक cxl_check_error(काष्ठा cxl_afu *afu);
पूर्णांक cxl_afu_slbia(काष्ठा cxl_afu *afu);
पूर्णांक cxl_data_cache_flush(काष्ठा cxl *adapter);
पूर्णांक cxl_afu_disable(काष्ठा cxl_afu *afu);
पूर्णांक cxl_psl_purge(काष्ठा cxl_afu *afu);
पूर्णांक cxl_calc_capp_routing(काष्ठा pci_dev *dev, u64 *chipid,
			  u32 *phb_index, u64 *capp_unit_id);
पूर्णांक cxl_slot_is_चयनed(काष्ठा pci_dev *dev);
पूर्णांक cxl_get_xsl9_dsnctl(काष्ठा pci_dev *dev, u64 capp_unit_id, u64 *reg);
u64 cxl_calculate_sr(bool master, bool kernel, bool real_mode, bool p9);

व्योम cxl_native_irq_dump_regs_psl9(काष्ठा cxl_context *ctx);
व्योम cxl_native_irq_dump_regs_psl8(काष्ठा cxl_context *ctx);
व्योम cxl_native_err_irq_dump_regs_psl8(काष्ठा cxl *adapter);
व्योम cxl_native_err_irq_dump_regs_psl9(काष्ठा cxl *adapter);
पूर्णांक cxl_pci_vphb_add(काष्ठा cxl_afu *afu);
व्योम cxl_pci_vphb_हटाओ(काष्ठा cxl_afu *afu);
व्योम cxl_release_mapping(काष्ठा cxl_context *ctx);

बाह्य काष्ठा pci_driver cxl_pci_driver;
बाह्य काष्ठा platक्रमm_driver cxl_of_driver;
पूर्णांक afu_allocate_irqs(काष्ठा cxl_context *ctx, u32 count);

पूर्णांक afu_खोलो(काष्ठा inode *inode, काष्ठा file *file);
पूर्णांक afu_release(काष्ठा inode *inode, काष्ठा file *file);
दीर्घ afu_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक afu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vm);
__poll_t afu_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *poll);
sमाप_प्रकार afu_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *off);
बाह्य स्थिर काष्ठा file_operations afu_fops;

काष्ठा cxl *cxl_guest_init_adapter(काष्ठा device_node *np, काष्ठा platक्रमm_device *dev);
व्योम cxl_guest_हटाओ_adapter(काष्ठा cxl *adapter);
पूर्णांक cxl_of_पढ़ो_adapter_handle(काष्ठा cxl *adapter, काष्ठा device_node *np);
पूर्णांक cxl_of_पढ़ो_adapter_properties(काष्ठा cxl *adapter, काष्ठा device_node *np);
sमाप_प्रकार cxl_guest_पढ़ो_adapter_vpd(काष्ठा cxl *adapter, व्योम *buf, माप_प्रकार len);
sमाप_प्रकार cxl_guest_पढ़ो_afu_vpd(काष्ठा cxl_afu *afu, व्योम *buf, माप_प्रकार len);
पूर्णांक cxl_guest_init_afu(काष्ठा cxl *adapter, पूर्णांक slice, काष्ठा device_node *afu_np);
व्योम cxl_guest_हटाओ_afu(काष्ठा cxl_afu *afu);
पूर्णांक cxl_of_पढ़ो_afu_handle(काष्ठा cxl_afu *afu, काष्ठा device_node *afu_np);
पूर्णांक cxl_of_पढ़ो_afu_properties(काष्ठा cxl_afu *afu, काष्ठा device_node *afu_np);
पूर्णांक cxl_guest_add_अक्षरdev(काष्ठा cxl *adapter);
व्योम cxl_guest_हटाओ_अक्षरdev(काष्ठा cxl *adapter);
व्योम cxl_guest_reload_module(काष्ठा cxl *adapter);
पूर्णांक cxl_of_probe(काष्ठा platक्रमm_device *pdev);

काष्ठा cxl_backend_ops अणु
	काष्ठा module *module;
	पूर्णांक (*adapter_reset)(काष्ठा cxl *adapter);
	पूर्णांक (*alloc_one_irq)(काष्ठा cxl *adapter);
	व्योम (*release_one_irq)(काष्ठा cxl *adapter, पूर्णांक hwirq);
	पूर्णांक (*alloc_irq_ranges)(काष्ठा cxl_irq_ranges *irqs,
				काष्ठा cxl *adapter, अचिन्हित पूर्णांक num);
	व्योम (*release_irq_ranges)(काष्ठा cxl_irq_ranges *irqs,
				काष्ठा cxl *adapter);
	पूर्णांक (*setup_irq)(काष्ठा cxl *adapter, अचिन्हित पूर्णांक hwirq,
			अचिन्हित पूर्णांक virq);
	irqवापस_t (*handle_psl_slice_error)(काष्ठा cxl_context *ctx,
					u64 dsisr, u64 errstat);
	irqवापस_t (*psl_पूर्णांकerrupt)(पूर्णांक irq, व्योम *data);
	पूर्णांक (*ack_irq)(काष्ठा cxl_context *ctx, u64 tfc, u64 psl_reset_mask);
	व्योम (*irq_रुको)(काष्ठा cxl_context *ctx);
	पूर्णांक (*attach_process)(काष्ठा cxl_context *ctx, bool kernel,
			u64 wed, u64 amr);
	पूर्णांक (*detach_process)(काष्ठा cxl_context *ctx);
	व्योम (*update_ivtes)(काष्ठा cxl_context *ctx);
	bool (*support_attributes)(स्थिर अक्षर *attr_name, क्रमागत cxl_attrs type);
	bool (*link_ok)(काष्ठा cxl *cxl, काष्ठा cxl_afu *afu);
	व्योम (*release_afu)(काष्ठा device *dev);
	sमाप_प्रकार (*afu_पढ़ो_err_buffer)(काष्ठा cxl_afu *afu, अक्षर *buf,
				loff_t off, माप_प्रकार count);
	पूर्णांक (*afu_check_and_enable)(काष्ठा cxl_afu *afu);
	पूर्णांक (*afu_activate_mode)(काष्ठा cxl_afu *afu, पूर्णांक mode);
	पूर्णांक (*afu_deactivate_mode)(काष्ठा cxl_afu *afu, पूर्णांक mode);
	पूर्णांक (*afu_reset)(काष्ठा cxl_afu *afu);
	पूर्णांक (*afu_cr_पढ़ो8)(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset, u8 *val);
	पूर्णांक (*afu_cr_पढ़ो16)(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset, u16 *val);
	पूर्णांक (*afu_cr_पढ़ो32)(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset, u32 *val);
	पूर्णांक (*afu_cr_पढ़ो64)(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset, u64 *val);
	पूर्णांक (*afu_cr_ग_लिखो8)(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset, u8 val);
	पूर्णांक (*afu_cr_ग_लिखो16)(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset, u16 val);
	पूर्णांक (*afu_cr_ग_लिखो32)(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset, u32 val);
	sमाप_प्रकार (*पढ़ो_adapter_vpd)(काष्ठा cxl *adapter, व्योम *buf, माप_प्रकार count);
पूर्ण;
बाह्य स्थिर काष्ठा cxl_backend_ops cxl_native_ops;
बाह्य स्थिर काष्ठा cxl_backend_ops cxl_guest_ops;
बाह्य स्थिर काष्ठा cxl_backend_ops *cxl_ops;

/* check अगर the given pci_dev is on the the cxl vphb bus */
bool cxl_pci_is_vphb_device(काष्ठा pci_dev *dev);

/* decode AFU error bits in the PSL रेजिस्टर PSL_SERR_An */
व्योम cxl_afu_decode_psl_serr(काष्ठा cxl_afu *afu, u64 serr);

/*
 * Increments the number of attached contexts on an adapter.
 * In हाल an adapter_context_lock is taken the वापस -EBUSY.
 */
पूर्णांक cxl_adapter_context_get(काष्ठा cxl *adapter);

/* Decrements the number of attached contexts on an adapter */
व्योम cxl_adapter_context_put(काष्ठा cxl *adapter);

/* If no active contexts then prevents contexts from being attached */
पूर्णांक cxl_adapter_context_lock(काष्ठा cxl *adapter);

/* Unlock the contexts-lock अगर taken. Warn and क्रमce unlock otherwise */
व्योम cxl_adapter_context_unlock(काष्ठा cxl *adapter);

/* Increases the reference count to "struct mm_struct" */
व्योम cxl_context_mm_count_get(काष्ठा cxl_context *ctx);

/* Decrements the reference count to "struct mm_struct" */
व्योम cxl_context_mm_count_put(काष्ठा cxl_context *ctx);

#पूर्ण_अगर
