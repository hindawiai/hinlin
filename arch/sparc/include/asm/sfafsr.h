<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_SFAFSR_H
#घोषणा _SPARC64_SFAFSR_H

#समावेश <linux/स्थिर.h>

/* Spitfire Asynchronous Fault Status रेजिस्टर, ASI=0x4C VA<63:0>=0x0 */

#घोषणा SFAFSR_ME		(_AC(1,UL) << SFAFSR_ME_SHIFT)
#घोषणा SFAFSR_ME_SHIFT		32
#घोषणा SFAFSR_PRIV		(_AC(1,UL) << SFAFSR_PRIV_SHIFT)
#घोषणा SFAFSR_PRIV_SHIFT	31
#घोषणा SFAFSR_ISAP		(_AC(1,UL) << SFAFSR_ISAP_SHIFT)
#घोषणा SFAFSR_ISAP_SHIFT	30
#घोषणा SFAFSR_ETP		(_AC(1,UL) << SFAFSR_ETP_SHIFT)
#घोषणा SFAFSR_ETP_SHIFT	29
#घोषणा SFAFSR_IVUE		(_AC(1,UL) << SFAFSR_IVUE_SHIFT)
#घोषणा SFAFSR_IVUE_SHIFT	28
#घोषणा SFAFSR_TO		(_AC(1,UL) << SFAFSR_TO_SHIFT)
#घोषणा SFAFSR_TO_SHIFT		27
#घोषणा SFAFSR_BERR		(_AC(1,UL) << SFAFSR_BERR_SHIFT)
#घोषणा SFAFSR_BERR_SHIFT	26
#घोषणा SFAFSR_LDP		(_AC(1,UL) << SFAFSR_LDP_SHIFT)
#घोषणा SFAFSR_LDP_SHIFT	25
#घोषणा SFAFSR_CP		(_AC(1,UL) << SFAFSR_CP_SHIFT)
#घोषणा SFAFSR_CP_SHIFT		24
#घोषणा SFAFSR_WP		(_AC(1,UL) << SFAFSR_WP_SHIFT)
#घोषणा SFAFSR_WP_SHIFT		23
#घोषणा SFAFSR_EDP		(_AC(1,UL) << SFAFSR_EDP_SHIFT)
#घोषणा SFAFSR_EDP_SHIFT	22
#घोषणा SFAFSR_UE		(_AC(1,UL) << SFAFSR_UE_SHIFT)
#घोषणा SFAFSR_UE_SHIFT		21
#घोषणा SFAFSR_CE		(_AC(1,UL) << SFAFSR_CE_SHIFT)
#घोषणा SFAFSR_CE_SHIFT		20
#घोषणा SFAFSR_ETS		(_AC(0xf,UL) << SFAFSR_ETS_SHIFT)
#घोषणा SFAFSR_ETS_SHIFT	16
#घोषणा SFAFSR_PSYND		(_AC(0xffff,UL) << SFAFSR_PSYND_SHIFT)
#घोषणा SFAFSR_PSYND_SHIFT	0

/* UDB Error Register, ASI=0x7f VA<63:0>=0x0(High),0x18(Low) क्रम पढ़ो
 *                     ASI=0x77 VA<63:0>=0x0(High),0x18(Low) क्रम ग_लिखो
 */

#घोषणा UDBE_UE			(_AC(1,UL) << 9)
#घोषणा UDBE_CE			(_AC(1,UL) << 8)
#घोषणा UDBE_E_SYNDR		(_AC(0xff,UL) << 0)

/* The trap handlers क्रम asynchronous errors encode the AFSR and
 * other pieces of inक्रमmation पूर्णांकo a 64-bit argument क्रम C code
 * encoded as follows:
 *
 * -----------------------------------------------
 * |  UDB_H  |  UDB_L  | TL>1  |  TT  |   AFSR   |
 * -----------------------------------------------
 *  63     54 53     44    42   41  33 32       0
 *
 * The AFAR is passed in unchanged.
 */
#घोषणा SFSTAT_UDBH_MASK	(_AC(0x3ff,UL) << SFSTAT_UDBH_SHIFT)
#घोषणा SFSTAT_UDBH_SHIFT	54
#घोषणा SFSTAT_UDBL_MASK	(_AC(0x3ff,UL) << SFSTAT_UDBH_SHIFT)
#घोषणा SFSTAT_UDBL_SHIFT	44
#घोषणा SFSTAT_TL_GT_ONE	(_AC(1,UL) << SFSTAT_TL_GT_ONE_SHIFT)
#घोषणा SFSTAT_TL_GT_ONE_SHIFT	42
#घोषणा SFSTAT_TRAP_TYPE	(_AC(0x1FF,UL) << SFSTAT_TRAP_TYPE_SHIFT)
#घोषणा SFSTAT_TRAP_TYPE_SHIFT	33
#घोषणा SFSTAT_AFSR_MASK	(_AC(0x1ffffffff,UL) << SFSTAT_AFSR_SHIFT)
#घोषणा SFSTAT_AFSR_SHIFT	0

/* ESTATE Error Enable Register, ASI=0x4b VA<63:0>=0x0 */
#घोषणा ESTATE_ERR_CE		0x1 /* Correctable errors                    */
#घोषणा ESTATE_ERR_NCE		0x2 /* TO, BERR, LDP, ETP, EDP, WP, UE, IVUE */
#घोषणा ESTATE_ERR_ISAP		0x4 /* System address parity error           */
#घोषणा ESTATE_ERR_ALL		(ESTATE_ERR_CE | \
				 ESTATE_ERR_NCE | \
				 ESTATE_ERR_ISAP)

/* The various trap types that report using the above state. */
#घोषणा TRAP_TYPE_IAE		0x09 /* Inकाष्ठाion Access Error             */
#घोषणा TRAP_TYPE_DAE		0x32 /* Data Access Error                    */
#घोषणा TRAP_TYPE_CEE		0x63 /* Correctable ECC Error                */

#पूर्ण_अगर /* _SPARC64_SFAFSR_H */
