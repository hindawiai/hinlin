<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_CHAFSR_H
#घोषणा _SPARC64_CHAFSR_H

/* Cheetah Asynchronous Fault Status रेजिस्टर, ASI=0x4C VA<63:0>=0x0 */

/* Comments indicate which processor variants on which the bit definition
 * is valid.  Codes are:
 * ch	-->	cheetah
 * ch+	-->	cheetah plus
 * jp	-->	jalapeno
 */

/* All bits of this रेजिस्टर except M_SYNDROME and E_SYNDROME are
 * पढ़ो, ग_लिखो 1 to clear.  M_SYNDROME and E_SYNDROME are पढ़ो-only.
 */

/* Software bit set by linux trap handlers to indicate that the trap was
 * संकेतled at %tl >= 1.
 */
#घोषणा CHAFSR_TL1		(1UL << 63UL) /* n/a */

/* Unmapped error from प्रणाली bus क्रम prefetch queue or
 * store queue पढ़ो operation
 */
#घोषणा CHPAFSR_DTO		(1UL << 59UL) /* ch+ */

/* Bus error from प्रणाली bus क्रम prefetch queue or store queue
 * पढ़ो operation
 */
#घोषणा CHPAFSR_DBERR		(1UL << 58UL) /* ch+ */

/* Hardware corrected E-cache Tag ECC error */
#घोषणा CHPAFSR_THCE		(1UL << 57UL) /* ch+ */
/* System पूर्णांकerface protocol error, hw समयout caused */
#घोषणा JPAFSR_JETO		(1UL << 57UL) /* jp */

/* SW handled correctable E-cache Tag ECC error */
#घोषणा CHPAFSR_TSCE		(1UL << 56UL) /* ch+ */
/* Parity error on प्रणाली snoop results */
#घोषणा JPAFSR_SCE		(1UL << 56UL) /* jp */

/* Uncorrectable E-cache Tag ECC error */
#घोषणा CHPAFSR_TUE		(1UL << 55UL) /* ch+ */
/* System पूर्णांकerface protocol error, illegal command detected */
#घोषणा JPAFSR_JEIC		(1UL << 55UL) /* jp */

/* Uncorrectable प्रणाली bus data ECC error due to prefetch
 * or store fill request
 */
#घोषणा CHPAFSR_DUE		(1UL << 54UL) /* ch+ */
/* System पूर्णांकerface protocol error, illegal ADTYPE detected */
#घोषणा JPAFSR_JEIT		(1UL << 54UL) /* jp */

/* Multiple errors of the same type have occurred.  This bit is set when
 * an uncorrectable error or a SW correctable error occurs and the status
 * bit to report that error is alपढ़ोy set.  When multiple errors of
 * dअगरferent types are indicated by setting multiple status bits.
 *
 * This bit is not set अगर multiple HW corrected errors with the same
 * status bit occur, only uncorrectable and SW correctable ones have
 * this behavior.
 *
 * This bit is not set when multiple ECC errors happen within a single
 * 64-byte प्रणाली bus transaction.  Only the first ECC error in a 16-byte
 * subunit will be logged.  All errors in subsequent 16-byte subunits
 * from the same 64-byte transaction are ignored.
 */
#घोषणा CHAFSR_ME		(1UL << 53UL) /* ch,ch+,jp */

/* Privileged state error has occurred.  This is a capture of PSTATE.PRIV
 * at the समय the error is detected.
 */
#घोषणा CHAFSR_PRIV		(1UL << 52UL) /* ch,ch+,jp */

/* The following bits 51 (CHAFSR_PERR) to 33 (CHAFSR_CE) are sticky error
 * bits and record the most recently detected errors.  Bits accumulate
 * errors that have been detected since the last ग_लिखो to clear the bit.
 */

/* System पूर्णांकerface protocol error.  The processor निश्चितs its' ERROR
 * pin when this event occurs and it also logs a specअगरic cause code
 * पूर्णांकo a JTAG scannable flop.
 */
#घोषणा CHAFSR_PERR		(1UL << 51UL) /* ch,ch+,jp */

/* Internal processor error.  The processor निश्चितs its' ERROR
 * pin when this event occurs and it also logs a specअगरic cause code
 * पूर्णांकo a JTAG scannable flop.
 */
#घोषणा CHAFSR_IERR		(1UL << 50UL) /* ch,ch+,jp */

/* System request parity error on incoming address */
#घोषणा CHAFSR_ISAP		(1UL << 49UL) /* ch,ch+,jp */

/* HW Corrected प्रणाली bus MTAG ECC error */
#घोषणा CHAFSR_EMC		(1UL << 48UL) /* ch,ch+ */
/* Parity error on L2 cache tag SRAM */
#घोषणा JPAFSR_ETP		(1UL << 48UL) /* jp */

/* Uncorrectable प्रणाली bus MTAG ECC error */
#घोषणा CHAFSR_EMU		(1UL << 47UL) /* ch,ch+ */
/* Out of range memory error has occurred */
#घोषणा JPAFSR_OM		(1UL << 47UL) /* jp */

/* HW Corrected प्रणाली bus data ECC error क्रम पढ़ो of पूर्णांकerrupt vector */
#घोषणा CHAFSR_IVC		(1UL << 46UL) /* ch,ch+ */
/* Error due to unsupported store */
#घोषणा JPAFSR_UMS		(1UL << 46UL) /* jp */

/* Uncorrectable प्रणाली bus data ECC error क्रम पढ़ो of पूर्णांकerrupt vector */
#घोषणा CHAFSR_IVU		(1UL << 45UL) /* ch,ch+,jp */

/* Unmapped error from प्रणाली bus */
#घोषणा CHAFSR_TO		(1UL << 44UL) /* ch,ch+,jp */

/* Bus error response from प्रणाली bus */
#घोषणा CHAFSR_BERR		(1UL << 43UL) /* ch,ch+,jp */

/* SW Correctable E-cache ECC error क्रम inकाष्ठाion fetch or data access
 * other than block load.
 */
#घोषणा CHAFSR_UCC		(1UL << 42UL) /* ch,ch+,jp */

/* Uncorrectable E-cache ECC error क्रम inकाष्ठाion fetch or data access
 * other than block load.
 */
#घोषणा CHAFSR_UCU		(1UL << 41UL) /* ch,ch+,jp */

/* Copyout HW Corrected ECC error */
#घोषणा CHAFSR_CPC		(1UL << 40UL) /* ch,ch+,jp */

/* Copyout Uncorrectable ECC error */
#घोषणा CHAFSR_CPU		(1UL << 39UL) /* ch,ch+,jp */

/* HW Corrected ECC error from E-cache क्रम ग_लिखोback */
#घोषणा CHAFSR_WDC		(1UL << 38UL) /* ch,ch+,jp */

/* Uncorrectable ECC error from E-cache क्रम ग_लिखोback */
#घोषणा CHAFSR_WDU		(1UL << 37UL) /* ch,ch+,jp */

/* HW Corrected ECC error from E-cache क्रम store merge or block load */
#घोषणा CHAFSR_EDC		(1UL << 36UL) /* ch,ch+,jp */

/* Uncorrectable ECC error from E-cache क्रम store merge or block load */
#घोषणा CHAFSR_EDU		(1UL << 35UL) /* ch,ch+,jp */

/* Uncorrectable प्रणाली bus data ECC error क्रम पढ़ो of memory or I/O */
#घोषणा CHAFSR_UE		(1UL << 34UL) /* ch,ch+,jp */

/* HW Corrected प्रणाली bus data ECC error क्रम पढ़ो of memory or I/O */
#घोषणा CHAFSR_CE		(1UL << 33UL) /* ch,ch+,jp */

/* Uncorrectable ECC error from remote cache/memory */
#घोषणा JPAFSR_RUE		(1UL << 32UL) /* jp */

/* Correctable ECC error from remote cache/memory */
#घोषणा JPAFSR_RCE		(1UL << 31UL) /* jp */

/* JBUS parity error on वापसed पढ़ो data */
#घोषणा JPAFSR_BP		(1UL << 30UL) /* jp */

/* JBUS parity error on data क्रम ग_लिखोback or block store */
#घोषणा JPAFSR_WBP		(1UL << 29UL) /* jp */

/* Foreign पढ़ो to DRAM incurring correctable ECC error */
#घोषणा JPAFSR_FRC		(1UL << 28UL) /* jp */

/* Foreign पढ़ो to DRAM incurring uncorrectable ECC error */
#घोषणा JPAFSR_FRU		(1UL << 27UL) /* jp */

#घोषणा CHAFSR_ERRORS		(CHAFSR_PERR | CHAFSR_IERR | CHAFSR_ISAP | CHAFSR_EMC | \
				 CHAFSR_EMU | CHAFSR_IVC | CHAFSR_IVU | CHAFSR_TO | \
				 CHAFSR_BERR | CHAFSR_UCC | CHAFSR_UCU | CHAFSR_CPC | \
				 CHAFSR_CPU | CHAFSR_WDC | CHAFSR_WDU | CHAFSR_EDC | \
				 CHAFSR_EDU | CHAFSR_UE | CHAFSR_CE)
#घोषणा CHPAFSR_ERRORS		(CHPAFSR_DTO | CHPAFSR_DBERR | CHPAFSR_THCE | \
				 CHPAFSR_TSCE | CHPAFSR_TUE | CHPAFSR_DUE | \
				 CHAFSR_PERR | CHAFSR_IERR | CHAFSR_ISAP | CHAFSR_EMC | \
				 CHAFSR_EMU | CHAFSR_IVC | CHAFSR_IVU | CHAFSR_TO | \
				 CHAFSR_BERR | CHAFSR_UCC | CHAFSR_UCU | CHAFSR_CPC | \
				 CHAFSR_CPU | CHAFSR_WDC | CHAFSR_WDU | CHAFSR_EDC | \
				 CHAFSR_EDU | CHAFSR_UE | CHAFSR_CE)
#घोषणा JPAFSR_ERRORS		(JPAFSR_JETO | JPAFSR_SCE | JPAFSR_JEIC | \
				 JPAFSR_JEIT | CHAFSR_PERR | CHAFSR_IERR | \
				 CHAFSR_ISAP | JPAFSR_ETP | JPAFSR_OM | \
				 JPAFSR_UMS | CHAFSR_IVU | CHAFSR_TO | \
				 CHAFSR_BERR | CHAFSR_UCC | CHAFSR_UCU | \
				 CHAFSR_CPC | CHAFSR_CPU | CHAFSR_WDC | \
				 CHAFSR_WDU | CHAFSR_EDC | CHAFSR_EDU | \
				 CHAFSR_UE | CHAFSR_CE | JPAFSR_RUE | \
				 JPAFSR_RCE | JPAFSR_BP | JPAFSR_WBP | \
				 JPAFSR_FRC | JPAFSR_FRU)

/* Active JBUS request संकेत when error occurred */
#घोषणा JPAFSR_JBREQ		(0x7UL << 24UL) /* jp */
#घोषणा JPAFSR_JBREQ_SHIFT	24UL

/* L2 cache way inक्रमmation */
#घोषणा JPAFSR_ETW		(0x3UL << 22UL) /* jp */
#घोषणा JPAFSR_ETW_SHIFT	22UL

/* System bus MTAG ECC syndrome.  This field captures the status of the
 * first occurrence of the highest-priority error according to the M_SYND
 * overग_लिखो policy.  After the AFSR sticky bit, corresponding to the error
 * क्रम which the M_SYND is reported, is cleared, the contents of the M_SYND
 * field will be unchanged by will be unfrozen क्रम further error capture.
 */
#घोषणा CHAFSR_M_SYNDROME	(0xfUL << 16UL) /* ch,ch+,jp */
#घोषणा CHAFSR_M_SYNDROME_SHIFT	16UL

/* Agenid Id of the क्रमeign device causing the UE/CE errors */
#घोषणा JPAFSR_AID		(0x1fUL << 9UL) /* jp */
#घोषणा JPAFSR_AID_SHIFT	9UL

/* System bus or E-cache data ECC syndrome.  This field captures the status
 * of the first occurrence of the highest-priority error according to the
 * E_SYND overग_लिखो policy.  After the AFSR sticky bit, corresponding to the
 * error क्रम which the E_SYND is reported, is cleare, the contents of the E_SYND
 * field will be unchanged but will be unfrozen क्रम further error capture.
 */
#घोषणा CHAFSR_E_SYNDROME	(0x1ffUL << 0UL) /* ch,ch+,jp */
#घोषणा CHAFSR_E_SYNDROME_SHIFT	0UL

/* The AFSR must be explicitly cleared by software, it is not cleared स्वतःmatically
 * by a पढ़ो.  Writes to bits <51:33> with bits set will clear the corresponding
 * bits in the AFSR.  Bits associated with disrupting traps must be cleared beक्रमe
 * पूर्णांकerrupts are re-enabled to prevent multiple traps क्रम the same error.  I.e.
 * PSTATE.IE and AFSR bits control delivery of disrupting traps.
 *
 * Since there is only one AFAR, when multiple events have been logged by the
 * bits in the AFSR, at most one of these events will have its status captured
 * in the AFAR.  The highest priority of those event bits will get AFAR logging.
 * The AFAR will be unlocked and available to capture the address of another event
 * as soon as the one bit in AFSR that corresponds to the event logged in AFAR is
 * cleared.  For example, अगर AFSR.CE is detected, then AFSR.UE (which overग_लिखोs
 * the AFAR), and AFSR.UE is cleared by not AFSR.CE, then the AFAR will be unlocked
 * and पढ़ोy क्रम another event, even though AFSR.CE is still set.  The same rules
 * also apply to the M_SYNDROME and E_SYNDROME fields of the AFSR.
 */

#पूर्ण_अगर /* _SPARC64_CHAFSR_H */
