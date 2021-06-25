<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cpu.h>

#समावेश "mce_amd.h"

अटल काष्ठा amd_decoder_ops fam_ops;

अटल u8 xec_mask	 = 0xf;

अटल व्योम (*decode_dram_ecc)(पूर्णांक node_id, काष्ठा mce *m);

व्योम amd_रेजिस्टर_ecc_decoder(व्योम (*f)(पूर्णांक, काष्ठा mce *))
अणु
	decode_dram_ecc = f;
पूर्ण
EXPORT_SYMBOL_GPL(amd_रेजिस्टर_ecc_decoder);

व्योम amd_unरेजिस्टर_ecc_decoder(व्योम (*f)(पूर्णांक, काष्ठा mce *))
अणु
	अगर (decode_dram_ecc) अणु
		WARN_ON(decode_dram_ecc != f);

		decode_dram_ecc = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(amd_unरेजिस्टर_ecc_decoder);

/*
 * string representation क्रम the dअगरferent MCA reported error types, see F3x48
 * or MSR0000_0411.
 */

/* transaction type */
अटल स्थिर अक्षर * स्थिर tt_msgs[] = अणु "INSN", "DATA", "GEN", "RESV" पूर्ण;

/* cache level */
अटल स्थिर अक्षर * स्थिर ll_msgs[] = अणु "RESV", "L1", "L2", "L3/GEN" पूर्ण;

/* memory transaction type */
अटल स्थिर अक्षर * स्थिर rrrr_msgs[] = अणु
       "GEN", "RD", "WR", "DRD", "DWR", "IRD", "PRF", "EV", "SNP"
पूर्ण;

/* participating processor */
स्थिर अक्षर * स्थिर pp_msgs[] = अणु "SRC", "RES", "OBS", "GEN" पूर्ण;
EXPORT_SYMBOL_GPL(pp_msgs);

/* request समयout */
अटल स्थिर अक्षर * स्थिर to_msgs[] = अणु "no timeout", "timed out" पूर्ण;

/* memory or i/o */
अटल स्थिर अक्षर * स्थिर ii_msgs[] = अणु "MEM", "RESV", "IO", "GEN" पूर्ण;

/* पूर्णांकernal error type */
अटल स्थिर अक्षर * स्थिर uu_msgs[] = अणु "RESV", "RESV", "HWA", "RESV" पूर्ण;

अटल स्थिर अक्षर * स्थिर f15h_mc1_mce_desc[] = अणु
	"UC during a demand linefill from L2",
	"Parity error during data load from IC",
	"Parity error for IC valid bit",
	"Main tag parity error",
	"Parity error in prediction queue",
	"PFB data/address parity error",
	"Parity error in the branch status reg",
	"PFB promotion address error",
	"Tag error during probe/victimization",
	"Parity error for IC probe tag valid bit",
	"PFB non-cacheable bit parity error",
	"PFB valid bit parity error",			/* xec = 0xd */
	"Microcode Patch Buffer",			/* xec = 010 */
	"uop queue",
	"insn buffer",
	"predecode buffer",
	"fetch address FIFO",
	"dispatch uop queue"
पूर्ण;

अटल स्थिर अक्षर * स्थिर f15h_mc2_mce_desc[] = अणु
	"Fill ECC error on data fills",			/* xec = 0x4 */
	"Fill parity error on insn fills",
	"Prefetcher request FIFO parity error",
	"PRQ address parity error",
	"PRQ data parity error",
	"WCC Tag ECC error",
	"WCC Data ECC error",
	"WCB Data parity error",
	"VB Data ECC or parity error",
	"L2 Tag ECC error",				/* xec = 0x10 */
	"Hard L2 Tag ECC error",
	"Multiple hits on L2 tag",
	"XAB parity error",
	"PRB address parity error"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mc4_mce_desc[] = अणु
	"DRAM ECC error detected on the NB",
	"CRC error detected on HT link",
	"Link-defined sync error packets detected on HT link",
	"HT Master abort",
	"HT Target abort",
	"Invalid GART PTE entry during GART table walk",
	"Unsupported atomic RMW received from an IO link",
	"Watchdog timeout due to lack of progress",
	"DRAM ECC error detected on the NB",
	"SVM DMA Exclusion Vector error",
	"HT data error detected on link",
	"Protocol error (link, L3, probe filter)",
	"NB internal arrays parity error",
	"DRAM addr/ctl signals parity error",
	"IO link transmission error",
	"L3 data cache ECC error",			/* xec = 0x1c */
	"L3 cache tag error",
	"L3 LRU parity bits error",
	"ECC Error in the Probe Filter directory"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mc5_mce_desc[] = अणु
	"CPU Watchdog timer expire",
	"Wakeup array dest tag",
	"AG payload array",
	"EX payload array",
	"IDRF array",
	"Retire dispatch queue",
	"Mapper checkpoint array",
	"Physical register file EX0 port",
	"Physical register file EX1 port",
	"Physical register file AG0 port",
	"Physical register file AG1 port",
	"Flag register file",
	"DE error occurred",
	"Retire status queue"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mc6_mce_desc[] = अणु
	"Hardware Assertion",
	"Free List",
	"Physical Register File",
	"Retire Queue",
	"Scheduler table",
	"Status Register File",
पूर्ण;

/* Scalable MCA error strings */
अटल स्थिर अक्षर * स्थिर smca_ls_mce_desc[] = अणु
	"Load queue parity error",
	"Store queue parity error",
	"Miss address buffer payload parity error",
	"Level 1 TLB parity error",
	"DC Tag error type 5",
	"DC Tag error type 6",
	"DC Tag error type 1",
	"Internal error type 1",
	"Internal error type 2",
	"System Read Data Error Thread 0",
	"System Read Data Error Thread 1",
	"DC Tag error type 2",
	"DC Data error type 1 and poison consumption",
	"DC Data error type 2",
	"DC Data error type 3",
	"DC Tag error type 4",
	"Level 2 TLB parity error",
	"PDC parity error",
	"DC Tag error type 3",
	"DC Tag error type 5",
	"L2 Fill Data error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_ls2_mce_desc[] = अणु
	"An ECC error was detected on a data cache read by a probe or victimization",
	"An ECC error or L2 poison was detected on a data cache read by a load",
	"An ECC error was detected on a data cache read-modify-write by a store",
	"An ECC error or poison bit mismatch was detected on a tag read by a probe or victimization",
	"An ECC error or poison bit mismatch was detected on a tag read by a load",
	"An ECC error or poison bit mismatch was detected on a tag read by a store",
	"An ECC error was detected on an EMEM read by a load",
	"An ECC error was detected on an EMEM read-modify-write by a store",
	"A parity error was detected in an L1 TLB entry by any access",
	"A parity error was detected in an L2 TLB entry by any access",
	"A parity error was detected in a PWC entry by any access",
	"A parity error was detected in an STQ entry by any access",
	"A parity error was detected in an LDQ entry by any access",
	"A parity error was detected in a MAB entry by any access",
	"A parity error was detected in an SCB entry state field by any access",
	"A parity error was detected in an SCB entry address field by any access",
	"A parity error was detected in an SCB entry data field by any access",
	"A parity error was detected in a WCB entry by any access",
	"A poisoned line was detected in an SCB entry by any access",
	"A SystemReadDataError error was reported on read data returned from L2 for a load",
	"A SystemReadDataError error was reported on read data returned from L2 for an SCB store",
	"A SystemReadDataError error was reported on read data returned from L2 for a WCB store",
	"A hardware assertion error was reported",
	"A parity error was detected in an STLF, SCB EMEM entry or SRB store data by any access",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_अगर_mce_desc[] = अणु
	"Op Cache Microtag Probe Port Parity Error",
	"IC Microtag or Full Tag Multi-hit Error",
	"IC Full Tag Parity Error",
	"IC Data Array Parity Error",
	"Decoupling Queue PhysAddr Parity Error",
	"L0 ITLB Parity Error",
	"L1 ITLB Parity Error",
	"L2 ITLB Parity Error",
	"BPQ Thread 0 Snoop Parity Error",
	"BPQ Thread 1 Snoop Parity Error",
	"L1 BTB Multi-Match Error",
	"L2 BTB Multi-Match Error",
	"L2 Cache Response Poison Error",
	"System Read Data Error",
	"Hardware Assertion Error",
	"L1-TLB Multi-Hit",
	"L2-TLB Multi-Hit",
	"BSR Parity Error",
	"CT MCE",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_l2_mce_desc[] = अणु
	"L2M Tag Multiple-Way-Hit error",
	"L2M Tag or State Array ECC Error",
	"L2M Data Array ECC Error",
	"Hardware Assert Error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_de_mce_desc[] = अणु
	"Micro-op cache tag parity error",
	"Micro-op cache data parity error",
	"Instruction buffer parity error",
	"Micro-op queue parity error",
	"Instruction dispatch queue parity error",
	"Fetch address FIFO parity error",
	"Patch RAM data parity error",
	"Patch RAM sequencer parity error",
	"Micro-op buffer parity error",
	"Hardware Assertion MCA Error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_ex_mce_desc[] = अणु
	"Watchdog Timeout error",
	"Physical register file parity error",
	"Flag register file parity error",
	"Immediate displacement register file parity error",
	"Address generator payload parity error",
	"EX payload parity error",
	"Checkpoint queue parity error",
	"Retire dispatch queue parity error",
	"Retire status queue parity error",
	"Scheduling queue parity error",
	"Branch buffer queue parity error",
	"Hardware Assertion error",
	"Spec Map parity error",
	"Retire Map parity error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_fp_mce_desc[] = अणु
	"Physical register file (PRF) parity error",
	"Freelist (FL) parity error",
	"Schedule queue parity error",
	"NSQ parity error",
	"Retire queue (RQ) parity error",
	"Status register file (SRF) parity error",
	"Hardware assertion",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_l3_mce_desc[] = अणु
	"Shadow Tag Macro ECC Error",
	"Shadow Tag Macro Multi-way-hit Error",
	"L3M Tag ECC Error",
	"L3M Tag Multi-way-hit Error",
	"L3M Data ECC Error",
	"SDP Parity Error or SystemReadDataError from XI",
	"L3 Victim Queue Parity Error",
	"L3 Hardware Assertion",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_cs_mce_desc[] = अणु
	"Illegal Request",
	"Address Violation",
	"Security Violation",
	"Illegal Response",
	"Unexpected Response",
	"Request or Probe Parity Error",
	"Read Response Parity Error",
	"Atomic Request Parity Error",
	"Probe Filter ECC Error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_cs2_mce_desc[] = अणु
	"Illegal Request",
	"Address Violation",
	"Security Violation",
	"Illegal Response",
	"Unexpected Response",
	"Request or Probe Parity Error",
	"Read Response Parity Error",
	"Atomic Request Parity Error",
	"SDP read response had no match in the CS queue",
	"Probe Filter Protocol Error",
	"Probe Filter ECC Error",
	"SDP read response had an unexpected RETRY error",
	"Counter overflow error",
	"Counter underflow error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_pie_mce_desc[] = अणु
	"Hardware Assert",
	"Register security violation",
	"Link Error",
	"Poison data consumption",
	"A deferred error was detected in the DF"
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_umc_mce_desc[] = अणु
	"DRAM ECC error",
	"Data poison error",
	"SDP parity error",
	"Advanced peripheral bus error",
	"Address/Command parity error",
	"Write data CRC error",
	"DCQ SRAM ECC error",
	"AES SRAM ECC error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_pb_mce_desc[] = अणु
	"An ECC error in the Parameter Block RAM array",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_psp_mce_desc[] = अणु
	"An ECC or parity error in a PSP RAM instance",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_psp2_mce_desc[] = अणु
	"High SRAM ECC or parity error",
	"Low SRAM ECC or parity error",
	"Instruction Cache Bank 0 ECC or parity error",
	"Instruction Cache Bank 1 ECC or parity error",
	"Instruction Tag Ram 0 parity error",
	"Instruction Tag Ram 1 parity error",
	"Data Cache Bank 0 ECC or parity error",
	"Data Cache Bank 1 ECC or parity error",
	"Data Cache Bank 2 ECC or parity error",
	"Data Cache Bank 3 ECC or parity error",
	"Data Tag Bank 0 parity error",
	"Data Tag Bank 1 parity error",
	"Data Tag Bank 2 parity error",
	"Data Tag Bank 3 parity error",
	"Dirty Data Ram parity error",
	"TLB Bank 0 parity error",
	"TLB Bank 1 parity error",
	"System Hub Read Buffer ECC or parity error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_smu_mce_desc[] = अणु
	"An ECC or parity error in an SMU RAM instance",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_smu2_mce_desc[] = अणु
	"High SRAM ECC or parity error",
	"Low SRAM ECC or parity error",
	"Data Cache Bank A ECC or parity error",
	"Data Cache Bank B ECC or parity error",
	"Data Tag Cache Bank A ECC or parity error",
	"Data Tag Cache Bank B ECC or parity error",
	"Instruction Cache Bank A ECC or parity error",
	"Instruction Cache Bank B ECC or parity error",
	"Instruction Tag Cache Bank A ECC or parity error",
	"Instruction Tag Cache Bank B ECC or parity error",
	"System Hub Read Buffer ECC or parity error",
	"PHY RAM ECC error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_mp5_mce_desc[] = अणु
	"High SRAM ECC or parity error",
	"Low SRAM ECC or parity error",
	"Data Cache Bank A ECC or parity error",
	"Data Cache Bank B ECC or parity error",
	"Data Tag Cache Bank A ECC or parity error",
	"Data Tag Cache Bank B ECC or parity error",
	"Instruction Cache Bank A ECC or parity error",
	"Instruction Cache Bank B ECC or parity error",
	"Instruction Tag Cache Bank A ECC or parity error",
	"Instruction Tag Cache Bank B ECC or parity error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_nbio_mce_desc[] = अणु
	"ECC or Parity error",
	"PCIE error",
	"SDP ErrEvent error",
	"SDP Egress Poison Error",
	"IOHC Internal Poison Error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_pcie_mce_desc[] = अणु
	"CCIX PER Message logging",
	"CCIX Read Response with Status: Non-Data Error",
	"CCIX Write Response with Status: Non-Data Error",
	"CCIX Read Response with Status: Data Error",
	"CCIX Non-okay write response with data error",
पूर्ण;

काष्ठा smca_mce_desc अणु
	स्थिर अक्षर * स्थिर *descs;
	अचिन्हित पूर्णांक num_descs;
पूर्ण;

अटल काष्ठा smca_mce_desc smca_mce_descs[] = अणु
	[SMCA_LS]	= अणु smca_ls_mce_desc,	ARRAY_SIZE(smca_ls_mce_desc)	पूर्ण,
	[SMCA_LS_V2]	= अणु smca_ls2_mce_desc,	ARRAY_SIZE(smca_ls2_mce_desc)	पूर्ण,
	[SMCA_IF]	= अणु smca_अगर_mce_desc,	ARRAY_SIZE(smca_अगर_mce_desc)	पूर्ण,
	[SMCA_L2_CACHE]	= अणु smca_l2_mce_desc,	ARRAY_SIZE(smca_l2_mce_desc)	पूर्ण,
	[SMCA_DE]	= अणु smca_de_mce_desc,	ARRAY_SIZE(smca_de_mce_desc)	पूर्ण,
	[SMCA_EX]	= अणु smca_ex_mce_desc,	ARRAY_SIZE(smca_ex_mce_desc)	पूर्ण,
	[SMCA_FP]	= अणु smca_fp_mce_desc,	ARRAY_SIZE(smca_fp_mce_desc)	पूर्ण,
	[SMCA_L3_CACHE]	= अणु smca_l3_mce_desc,	ARRAY_SIZE(smca_l3_mce_desc)	पूर्ण,
	[SMCA_CS]	= अणु smca_cs_mce_desc,	ARRAY_SIZE(smca_cs_mce_desc)	पूर्ण,
	[SMCA_CS_V2]	= अणु smca_cs2_mce_desc,	ARRAY_SIZE(smca_cs2_mce_desc)	पूर्ण,
	[SMCA_PIE]	= अणु smca_pie_mce_desc,	ARRAY_SIZE(smca_pie_mce_desc)	पूर्ण,
	[SMCA_UMC]	= अणु smca_umc_mce_desc,	ARRAY_SIZE(smca_umc_mce_desc)	पूर्ण,
	[SMCA_PB]	= अणु smca_pb_mce_desc,	ARRAY_SIZE(smca_pb_mce_desc)	पूर्ण,
	[SMCA_PSP]	= अणु smca_psp_mce_desc,	ARRAY_SIZE(smca_psp_mce_desc)	पूर्ण,
	[SMCA_PSP_V2]	= अणु smca_psp2_mce_desc,	ARRAY_SIZE(smca_psp2_mce_desc)	पूर्ण,
	[SMCA_SMU]	= अणु smca_smu_mce_desc,	ARRAY_SIZE(smca_smu_mce_desc)	पूर्ण,
	[SMCA_SMU_V2]	= अणु smca_smu2_mce_desc,	ARRAY_SIZE(smca_smu2_mce_desc)	पूर्ण,
	[SMCA_MP5]	= अणु smca_mp5_mce_desc,	ARRAY_SIZE(smca_mp5_mce_desc)	पूर्ण,
	[SMCA_NBIO]	= अणु smca_nbio_mce_desc,	ARRAY_SIZE(smca_nbio_mce_desc)	पूर्ण,
	[SMCA_PCIE]	= अणु smca_pcie_mce_desc,	ARRAY_SIZE(smca_pcie_mce_desc)	पूर्ण,
पूर्ण;

अटल bool f12h_mc0_mce(u16 ec, u8 xec)
अणु
	bool ret = false;

	अगर (MEM_ERROR(ec)) अणु
		u8 ll = LL(ec);
		ret = true;

		अगर (ll == LL_L2)
			pr_cont("during L1 linefill from L2.\n");
		अन्यथा अगर (ll == LL_L1)
			pr_cont("Data/Tag %s error.\n", R4_MSG(ec));
		अन्यथा
			ret = false;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool f10h_mc0_mce(u16 ec, u8 xec)
अणु
	अगर (R4(ec) == R4_GEN && LL(ec) == LL_L1) अणु
		pr_cont("during data scrub.\n");
		वापस true;
	पूर्ण
	वापस f12h_mc0_mce(ec, xec);
पूर्ण

अटल bool k8_mc0_mce(u16 ec, u8 xec)
अणु
	अगर (BUS_ERROR(ec)) अणु
		pr_cont("during system linefill.\n");
		वापस true;
	पूर्ण

	वापस f10h_mc0_mce(ec, xec);
पूर्ण

अटल bool cat_mc0_mce(u16 ec, u8 xec)
अणु
	u8 r4	 = R4(ec);
	bool ret = true;

	अगर (MEM_ERROR(ec)) अणु

		अगर (TT(ec) != TT_DATA || LL(ec) != LL_L1)
			वापस false;

		चयन (r4) अणु
		हाल R4_DRD:
		हाल R4_DWR:
			pr_cont("Data/Tag parity error due to %s.\n",
				(r4 == R4_DRD ? "load/hw prf" : "store"));
			अवरोध;
		हाल R4_EVICT:
			pr_cont("Copyback parity error on a tag miss.\n");
			अवरोध;
		हाल R4_SNOOP:
			pr_cont("Tag parity error during snoop.\n");
			अवरोध;
		शेष:
			ret = false;
		पूर्ण
	पूर्ण अन्यथा अगर (BUS_ERROR(ec)) अणु

		अगर ((II(ec) != II_MEM && II(ec) != II_IO) || LL(ec) != LL_LG)
			वापस false;

		pr_cont("System read data error on a ");

		चयन (r4) अणु
		हाल R4_RD:
			pr_cont("TLB reload.\n");
			अवरोध;
		हाल R4_DWR:
			pr_cont("store.\n");
			अवरोध;
		हाल R4_DRD:
			pr_cont("load.\n");
			अवरोध;
		शेष:
			ret = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool f15h_mc0_mce(u16 ec, u8 xec)
अणु
	bool ret = true;

	अगर (MEM_ERROR(ec)) अणु

		चयन (xec) अणु
		हाल 0x0:
			pr_cont("Data Array access error.\n");
			अवरोध;

		हाल 0x1:
			pr_cont("UC error during a linefill from L2/NB.\n");
			अवरोध;

		हाल 0x2:
		हाल 0x11:
			pr_cont("STQ access error.\n");
			अवरोध;

		हाल 0x3:
			pr_cont("SCB access error.\n");
			अवरोध;

		हाल 0x10:
			pr_cont("Tag error.\n");
			अवरोध;

		हाल 0x12:
			pr_cont("LDQ access error.\n");
			अवरोध;

		शेष:
			ret = false;
		पूर्ण
	पूर्ण अन्यथा अगर (BUS_ERROR(ec)) अणु

		अगर (!xec)
			pr_cont("System Read Data Error.\n");
		अन्यथा
			pr_cont(" Internal error condition type %d.\n", xec);
	पूर्ण अन्यथा अगर (INT_ERROR(ec)) अणु
		अगर (xec <= 0x1f)
			pr_cont("Hardware Assert.\n");
		अन्यथा
			ret = false;

	पूर्ण अन्यथा
		ret = false;

	वापस ret;
पूर्ण

अटल व्योम decode_mc0_mce(काष्ठा mce *m)
अणु
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	pr_emerg(HW_ERR "MC0 Error: ");

	/* TLB error signatures are the same across families */
	अगर (TLB_ERROR(ec)) अणु
		अगर (TT(ec) == TT_DATA) अणु
			pr_cont("%s TLB %s.\n", LL_MSG(ec),
				((xec == 2) ? "locked miss"
					    : (xec ? "multimatch" : "parity")));
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (fam_ops.mc0_mce(ec, xec))
		;
	अन्यथा
		pr_emerg(HW_ERR "Corrupted MC0 MCE info?\n");
पूर्ण

अटल bool k8_mc1_mce(u16 ec, u8 xec)
अणु
	u8 ll	 = LL(ec);
	bool ret = true;

	अगर (!MEM_ERROR(ec))
		वापस false;

	अगर (ll == 0x2)
		pr_cont("during a linefill from L2.\n");
	अन्यथा अगर (ll == 0x1) अणु
		चयन (R4(ec)) अणु
		हाल R4_IRD:
			pr_cont("Parity error during data load.\n");
			अवरोध;

		हाल R4_EVICT:
			pr_cont("Copyback Parity/Victim error.\n");
			अवरोध;

		हाल R4_SNOOP:
			pr_cont("Tag Snoop error.\n");
			अवरोध;

		शेष:
			ret = false;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		ret = false;

	वापस ret;
पूर्ण

अटल bool cat_mc1_mce(u16 ec, u8 xec)
अणु
	u8 r4    = R4(ec);
	bool ret = true;

	अगर (!MEM_ERROR(ec))
		वापस false;

	अगर (TT(ec) != TT_INSTR)
		वापस false;

	अगर (r4 == R4_IRD)
		pr_cont("Data/tag array parity error for a tag hit.\n");
	अन्यथा अगर (r4 == R4_SNOOP)
		pr_cont("Tag error during snoop/victimization.\n");
	अन्यथा अगर (xec == 0x0)
		pr_cont("Tag parity error from victim castout.\n");
	अन्यथा अगर (xec == 0x2)
		pr_cont("Microcode patch RAM parity error.\n");
	अन्यथा
		ret = false;

	वापस ret;
पूर्ण

अटल bool f15h_mc1_mce(u16 ec, u8 xec)
अणु
	bool ret = true;

	अगर (!MEM_ERROR(ec))
		वापस false;

	चयन (xec) अणु
	हाल 0x0 ... 0xa:
		pr_cont("%s.\n", f15h_mc1_mce_desc[xec]);
		अवरोध;

	हाल 0xd:
		pr_cont("%s.\n", f15h_mc1_mce_desc[xec-2]);
		अवरोध;

	हाल 0x10:
		pr_cont("%s.\n", f15h_mc1_mce_desc[xec-4]);
		अवरोध;

	हाल 0x11 ... 0x15:
		pr_cont("Decoder %s parity error.\n", f15h_mc1_mce_desc[xec-4]);
		अवरोध;

	शेष:
		ret = false;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम decode_mc1_mce(काष्ठा mce *m)
अणु
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	pr_emerg(HW_ERR "MC1 Error: ");

	अगर (TLB_ERROR(ec))
		pr_cont("%s TLB %s.\n", LL_MSG(ec),
			(xec ? "multimatch" : "parity error"));
	अन्यथा अगर (BUS_ERROR(ec)) अणु
		bool k8 = (boot_cpu_data.x86 == 0xf && (m->status & BIT_64(58)));

		pr_cont("during %s.\n", (k8 ? "system linefill" : "NB data read"));
	पूर्ण अन्यथा अगर (INT_ERROR(ec)) अणु
		अगर (xec <= 0x3f)
			pr_cont("Hardware Assert.\n");
		अन्यथा
			जाओ wrong_mc1_mce;
	पूर्ण अन्यथा अगर (fam_ops.mc1_mce(ec, xec))
		;
	अन्यथा
		जाओ wrong_mc1_mce;

	वापस;

wrong_mc1_mce:
	pr_emerg(HW_ERR "Corrupted MC1 MCE info?\n");
पूर्ण

अटल bool k8_mc2_mce(u16 ec, u8 xec)
अणु
	bool ret = true;

	अगर (xec == 0x1)
		pr_cont(" in the write data buffers.\n");
	अन्यथा अगर (xec == 0x3)
		pr_cont(" in the victim data buffers.\n");
	अन्यथा अगर (xec == 0x2 && MEM_ERROR(ec))
		pr_cont(": %s error in the L2 cache tags.\n", R4_MSG(ec));
	अन्यथा अगर (xec == 0x0) अणु
		अगर (TLB_ERROR(ec))
			pr_cont("%s error in a Page Descriptor Cache or Guest TLB.\n",
				TT_MSG(ec));
		अन्यथा अगर (BUS_ERROR(ec))
			pr_cont(": %s/ECC error in data read from NB: %s.\n",
				R4_MSG(ec), PP_MSG(ec));
		अन्यथा अगर (MEM_ERROR(ec)) अणु
			u8 r4 = R4(ec);

			अगर (r4 >= 0x7)
				pr_cont(": %s error during data copyback.\n",
					R4_MSG(ec));
			अन्यथा अगर (r4 <= 0x1)
				pr_cont(": %s parity/ECC error during data "
					"access from L2.\n", R4_MSG(ec));
			अन्यथा
				ret = false;
		पूर्ण अन्यथा
			ret = false;
	पूर्ण अन्यथा
		ret = false;

	वापस ret;
पूर्ण

अटल bool f15h_mc2_mce(u16 ec, u8 xec)
अणु
	bool ret = true;

	अगर (TLB_ERROR(ec)) अणु
		अगर (xec == 0x0)
			pr_cont("Data parity TLB read error.\n");
		अन्यथा अगर (xec == 0x1)
			pr_cont("Poison data provided for TLB fill.\n");
		अन्यथा
			ret = false;
	पूर्ण अन्यथा अगर (BUS_ERROR(ec)) अणु
		अगर (xec > 2)
			ret = false;

		pr_cont("Error during attempted NB data read.\n");
	पूर्ण अन्यथा अगर (MEM_ERROR(ec)) अणु
		चयन (xec) अणु
		हाल 0x4 ... 0xc:
			pr_cont("%s.\n", f15h_mc2_mce_desc[xec - 0x4]);
			अवरोध;

		हाल 0x10 ... 0x14:
			pr_cont("%s.\n", f15h_mc2_mce_desc[xec - 0x7]);
			अवरोध;

		शेष:
			ret = false;
		पूर्ण
	पूर्ण अन्यथा अगर (INT_ERROR(ec)) अणु
		अगर (xec <= 0x3f)
			pr_cont("Hardware Assert.\n");
		अन्यथा
			ret = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool f16h_mc2_mce(u16 ec, u8 xec)
अणु
	u8 r4 = R4(ec);

	अगर (!MEM_ERROR(ec))
		वापस false;

	चयन (xec) अणु
	हाल 0x04 ... 0x05:
		pr_cont("%cBUFF parity error.\n", (r4 == R4_RD) ? 'I' : 'O');
		अवरोध;

	हाल 0x09 ... 0x0b:
	हाल 0x0d ... 0x0f:
		pr_cont("ECC error in L2 tag (%s).\n",
			((r4 == R4_GEN)   ? "BankReq" :
			((r4 == R4_SNOOP) ? "Prb"     : "Fill")));
		अवरोध;

	हाल 0x10 ... 0x19:
	हाल 0x1b:
		pr_cont("ECC error in L2 data array (%s).\n",
			(((r4 == R4_RD) && !(xec & 0x3)) ? "Hit"  :
			((r4 == R4_GEN)   ? "Attr" :
			((r4 == R4_EVICT) ? "Vict" : "Fill"))));
		अवरोध;

	हाल 0x1c ... 0x1d:
	हाल 0x1f:
		pr_cont("Parity error in L2 attribute bits (%s).\n",
			((r4 == R4_RD)  ? "Hit"  :
			((r4 == R4_GEN) ? "Attr" : "Fill")));
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम decode_mc2_mce(काष्ठा mce *m)
अणु
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	pr_emerg(HW_ERR "MC2 Error: ");

	अगर (!fam_ops.mc2_mce(ec, xec))
		pr_cont(HW_ERR "Corrupted MC2 MCE info?\n");
पूर्ण

अटल व्योम decode_mc3_mce(काष्ठा mce *m)
अणु
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	अगर (boot_cpu_data.x86 >= 0x14) अणु
		pr_emerg("You shouldn't be seeing MC3 MCE on this cpu family,"
			 " please report on LKML.\n");
		वापस;
	पूर्ण

	pr_emerg(HW_ERR "MC3 Error");

	अगर (xec == 0x0) अणु
		u8 r4 = R4(ec);

		अगर (!BUS_ERROR(ec) || (r4 != R4_DRD && r4 != R4_DWR))
			जाओ wrong_mc3_mce;

		pr_cont(" during %s.\n", R4_MSG(ec));
	पूर्ण अन्यथा
		जाओ wrong_mc3_mce;

	वापस;

 wrong_mc3_mce:
	pr_emerg(HW_ERR "Corrupted MC3 MCE info?\n");
पूर्ण

अटल व्योम decode_mc4_mce(काष्ठा mce *m)
अणु
	अचिन्हित पूर्णांक fam = x86_family(m->cpuid);
	पूर्णांक node_id = topology_die_id(m->extcpu);
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, 0x1f);
	u8 offset = 0;

	pr_emerg(HW_ERR "MC4 Error (node %d): ", node_id);

	चयन (xec) अणु
	हाल 0x0 ... 0xe:

		/* special handling क्रम DRAM ECCs */
		अगर (xec == 0x0 || xec == 0x8) अणु
			/* no ECCs on F11h */
			अगर (fam == 0x11)
				जाओ wrong_mc4_mce;

			pr_cont("%s.\n", mc4_mce_desc[xec]);

			अगर (decode_dram_ecc)
				decode_dram_ecc(node_id, m);
			वापस;
		पूर्ण
		अवरोध;

	हाल 0xf:
		अगर (TLB_ERROR(ec))
			pr_cont("GART Table Walk data error.\n");
		अन्यथा अगर (BUS_ERROR(ec))
			pr_cont("DMA Exclusion Vector Table Walk error.\n");
		अन्यथा
			जाओ wrong_mc4_mce;
		वापस;

	हाल 0x19:
		अगर (fam == 0x15 || fam == 0x16)
			pr_cont("Compute Unit Data Error.\n");
		अन्यथा
			जाओ wrong_mc4_mce;
		वापस;

	हाल 0x1c ... 0x1f:
		offset = 13;
		अवरोध;

	शेष:
		जाओ wrong_mc4_mce;
	पूर्ण

	pr_cont("%s.\n", mc4_mce_desc[xec - offset]);
	वापस;

 wrong_mc4_mce:
	pr_emerg(HW_ERR "Corrupted MC4 MCE info?\n");
पूर्ण

अटल व्योम decode_mc5_mce(काष्ठा mce *m)
अणु
	अचिन्हित पूर्णांक fam = x86_family(m->cpuid);
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, xec_mask);

	अगर (fam == 0xf || fam == 0x11)
		जाओ wrong_mc5_mce;

	pr_emerg(HW_ERR "MC5 Error: ");

	अगर (INT_ERROR(ec)) अणु
		अगर (xec <= 0x1f) अणु
			pr_cont("Hardware Assert.\n");
			वापस;
		पूर्ण अन्यथा
			जाओ wrong_mc5_mce;
	पूर्ण

	अगर (xec == 0x0 || xec == 0xc)
		pr_cont("%s.\n", mc5_mce_desc[xec]);
	अन्यथा अगर (xec <= 0xd)
		pr_cont("%s parity error.\n", mc5_mce_desc[xec]);
	अन्यथा
		जाओ wrong_mc5_mce;

	वापस;

 wrong_mc5_mce:
	pr_emerg(HW_ERR "Corrupted MC5 MCE info?\n");
पूर्ण

अटल व्योम decode_mc6_mce(काष्ठा mce *m)
अणु
	u8 xec = XEC(m->status, xec_mask);

	pr_emerg(HW_ERR "MC6 Error: ");

	अगर (xec > 0x5)
		जाओ wrong_mc6_mce;

	pr_cont("%s parity error.\n", mc6_mce_desc[xec]);
	वापस;

 wrong_mc6_mce:
	pr_emerg(HW_ERR "Corrupted MC6 MCE info?\n");
पूर्ण

/* Decode errors according to Scalable MCA specअगरication */
अटल व्योम decode_smca_error(काष्ठा mce *m)
अणु
	काष्ठा smca_hwid *hwid;
	क्रमागत smca_bank_types bank_type;
	स्थिर अक्षर *ip_name;
	u8 xec = XEC(m->status, xec_mask);

	अगर (m->bank >= ARRAY_SIZE(smca_banks))
		वापस;

	hwid = smca_banks[m->bank].hwid;
	अगर (!hwid)
		वापस;

	bank_type = hwid->bank_type;

	अगर (bank_type == SMCA_RESERVED) अणु
		pr_emerg(HW_ERR "Bank %d is reserved.\n", m->bank);
		वापस;
	पूर्ण

	ip_name = smca_get_दीर्घ_name(bank_type);

	pr_emerg(HW_ERR "%s Ext. Error Code: %d", ip_name, xec);

	/* Only prपूर्णांक the decode of valid error codes */
	अगर (xec < smca_mce_descs[bank_type].num_descs)
		pr_cont(", %s.\n", smca_mce_descs[bank_type].descs[xec]);

	अगर (bank_type == SMCA_UMC && xec == 0 && decode_dram_ecc)
		decode_dram_ecc(topology_die_id(m->extcpu), m);
पूर्ण

अटल अंतरभूत व्योम amd_decode_err_code(u16 ec)
अणु
	अगर (INT_ERROR(ec)) अणु
		pr_emerg(HW_ERR "internal: %s\n", UU_MSG(ec));
		वापस;
	पूर्ण

	pr_emerg(HW_ERR "cache level: %s", LL_MSG(ec));

	अगर (BUS_ERROR(ec))
		pr_cont(", mem/io: %s", II_MSG(ec));
	अन्यथा
		pr_cont(", tx: %s", TT_MSG(ec));

	अगर (MEM_ERROR(ec) || BUS_ERROR(ec)) अणु
		pr_cont(", mem-tx: %s", R4_MSG(ec));

		अगर (BUS_ERROR(ec))
			pr_cont(", part-proc: %s (%s)", PP_MSG(ec), TO_MSG(ec));
	पूर्ण

	pr_cont("\n");
पूर्ण

अटल स्थिर अक्षर *decode_error_status(काष्ठा mce *m)
अणु
	अगर (m->status & MCI_STATUS_UC) अणु
		अगर (m->status & MCI_STATUS_PCC)
			वापस "System Fatal error.";
		अगर (m->mcgstatus & MCG_STATUS_RIPV)
			वापस "Uncorrected, software restartable error.";
		वापस "Uncorrected, software containable error.";
	पूर्ण

	अगर (m->status & MCI_STATUS_DEFERRED)
		वापस "Deferred error, no action required.";

	वापस "Corrected error, no action required.";
पूर्ण

अटल पूर्णांक
amd_decode_mce(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा mce *m = (काष्ठा mce *)data;
	अचिन्हित पूर्णांक fam = x86_family(m->cpuid);
	पूर्णांक ecc;

	अगर (m->kflags & MCE_HANDLED_CEC)
		वापस NOTIFY_DONE;

	pr_emerg(HW_ERR "%s\n", decode_error_status(m));

	pr_emerg(HW_ERR "CPU:%d (%x:%x:%x) MC%d_STATUS[%s|%s|%s|%s|%s",
		m->extcpu,
		fam, x86_model(m->cpuid), x86_stepping(m->cpuid),
		m->bank,
		((m->status & MCI_STATUS_OVER)	? "Over"  : "-"),
		((m->status & MCI_STATUS_UC)	? "UE"	  :
		 (m->status & MCI_STATUS_DEFERRED) ? "-"  : "CE"),
		((m->status & MCI_STATUS_MISCV)	? "MiscV" : "-"),
		((m->status & MCI_STATUS_ADDRV)	? "AddrV" : "-"),
		((m->status & MCI_STATUS_PCC)	? "PCC"	  : "-"));

	अगर (boot_cpu_has(X86_FEATURE_SMCA)) अणु
		u32 low, high;
		u32 addr = MSR_AMD64_SMCA_MCx_CONFIG(m->bank);

		अगर (!rdmsr_safe(addr, &low, &high) &&
		    (low & MCI_CONFIG_MCAX))
			pr_cont("|%s", ((m->status & MCI_STATUS_TCC) ? "TCC" : "-"));

		pr_cont("|%s", ((m->status & MCI_STATUS_SYNDV) ? "SyndV" : "-"));
	पूर्ण

	/* करो the two bits[14:13] together */
	ecc = (m->status >> 45) & 0x3;
	अगर (ecc)
		pr_cont("|%sECC", ((ecc == 2) ? "C" : "U"));

	अगर (fam >= 0x15) अणु
		pr_cont("|%s", (m->status & MCI_STATUS_DEFERRED ? "Deferred" : "-"));

		/* F15h, bank4, bit 43 is part of McaStatSubCache. */
		अगर (fam != 0x15 || m->bank != 4)
			pr_cont("|%s", (m->status & MCI_STATUS_POISON ? "Poison" : "-"));
	पूर्ण

	अगर (fam >= 0x17)
		pr_cont("|%s", (m->status & MCI_STATUS_SCRUB ? "Scrub" : "-"));

	pr_cont("]: 0x%016llx\n", m->status);

	अगर (m->status & MCI_STATUS_ADDRV)
		pr_emerg(HW_ERR "Error Addr: 0x%016llx\n", m->addr);

	अगर (m->ppin)
		pr_emerg(HW_ERR "PPIN: 0x%016llx\n", m->ppin);

	अगर (boot_cpu_has(X86_FEATURE_SMCA)) अणु
		pr_emerg(HW_ERR "IPID: 0x%016llx", m->ipid);

		अगर (m->status & MCI_STATUS_SYNDV)
			pr_cont(", Syndrome: 0x%016llx", m->synd);

		pr_cont("\n");

		decode_smca_error(m);
		जाओ err_code;
	पूर्ण

	अगर (m->tsc)
		pr_emerg(HW_ERR "TSC: %llu\n", m->tsc);

	/* Doesn't matter which member to test. */
	अगर (!fam_ops.mc0_mce)
		जाओ err_code;

	चयन (m->bank) अणु
	हाल 0:
		decode_mc0_mce(m);
		अवरोध;

	हाल 1:
		decode_mc1_mce(m);
		अवरोध;

	हाल 2:
		decode_mc2_mce(m);
		अवरोध;

	हाल 3:
		decode_mc3_mce(m);
		अवरोध;

	हाल 4:
		decode_mc4_mce(m);
		अवरोध;

	हाल 5:
		decode_mc5_mce(m);
		अवरोध;

	हाल 6:
		decode_mc6_mce(m);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

 err_code:
	amd_decode_err_code(m->status & 0xffff);

	m->kflags |= MCE_HANDLED_EDAC;
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block amd_mce_dec_nb = अणु
	.notअगरier_call	= amd_decode_mce,
	.priority	= MCE_PRIO_EDAC,
पूर्ण;

अटल पूर्णांक __init mce_amd_init(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	अगर (c->x86_venकरोr != X86_VENDOR_AMD &&
	    c->x86_venकरोr != X86_VENDOR_HYGON)
		वापस -ENODEV;

	अगर (boot_cpu_has(X86_FEATURE_SMCA)) अणु
		xec_mask = 0x3f;
		जाओ out;
	पूर्ण

	चयन (c->x86) अणु
	हाल 0xf:
		fam_ops.mc0_mce = k8_mc0_mce;
		fam_ops.mc1_mce = k8_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		अवरोध;

	हाल 0x10:
		fam_ops.mc0_mce = f10h_mc0_mce;
		fam_ops.mc1_mce = k8_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		अवरोध;

	हाल 0x11:
		fam_ops.mc0_mce = k8_mc0_mce;
		fam_ops.mc1_mce = k8_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		अवरोध;

	हाल 0x12:
		fam_ops.mc0_mce = f12h_mc0_mce;
		fam_ops.mc1_mce = k8_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		अवरोध;

	हाल 0x14:
		fam_ops.mc0_mce = cat_mc0_mce;
		fam_ops.mc1_mce = cat_mc1_mce;
		fam_ops.mc2_mce = k8_mc2_mce;
		अवरोध;

	हाल 0x15:
		xec_mask = c->x86_model == 0x60 ? 0x3f : 0x1f;

		fam_ops.mc0_mce = f15h_mc0_mce;
		fam_ops.mc1_mce = f15h_mc1_mce;
		fam_ops.mc2_mce = f15h_mc2_mce;
		अवरोध;

	हाल 0x16:
		xec_mask = 0x1f;
		fam_ops.mc0_mce = cat_mc0_mce;
		fam_ops.mc1_mce = cat_mc1_mce;
		fam_ops.mc2_mce = f16h_mc2_mce;
		अवरोध;

	हाल 0x17:
	हाल 0x18:
		pr_warn_once("Decoding supported only on Scalable MCA processors.\n");
		वापस -EINVAL;

	शेष:
		prपूर्णांकk(KERN_WARNING "Huh? What family is it: 0x%x?!\n", c->x86);
		वापस -EINVAL;
	पूर्ण

out:
	pr_info("MCE: In-kernel MCE decoding enabled.\n");

	mce_रेजिस्टर_decode_chain(&amd_mce_dec_nb);

	वापस 0;
पूर्ण
early_initcall(mce_amd_init);

#अगर_घोषित MODULE
अटल व्योम __निकास mce_amd_निकास(व्योम)
अणु
	mce_unरेजिस्टर_decode_chain(&amd_mce_dec_nb);
पूर्ण

MODULE_DESCRIPTION("AMD MCE decoder");
MODULE_ALIAS("edac-mce-amd");
MODULE_LICENSE("GPL");
module_निकास(mce_amd_निकास);
#पूर्ण_अगर
