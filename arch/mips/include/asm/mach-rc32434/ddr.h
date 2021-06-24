<शैली गुरु>
/*
 *  Definitions क्रम the DDR रेजिस्टरs
 *
 *  Copyright 2002 Ryan Holm <ryan.holmQVist@idt.com>
 *  Copyright 2008 Florian Fainelli <florian@खोलोwrt.org>
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#अगर_अघोषित _ASM_RC32434_DDR_H_
#घोषणा _ASM_RC32434_DDR_H_

#समावेश <यंत्र/mach-rc32434/rb.h>

/* DDR रेजिस्टर काष्ठाure */
काष्ठा ddr_ram अणु
	u32 ddrbase;
	u32 ddrmask;
	u32 res1;
	u32 res2;
	u32 ddrc;
	u32 ddrabase;
	u32 ddramask;
	u32 ddramap;
	u32 ddrcust;
	u32 ddrrdc;
	u32 ddrspare;
पूर्ण;

#घोषणा DDR0_PHYS_ADDR		0x18018000

/* DDR banks masks */
#घोषणा DDR_MASK		0xffff0000
#घोषणा DDR0_BASE_MSK		DDR_MASK
#घोषणा DDR1_BASE_MSK		DDR_MASK

/* DDR bank0 रेजिस्टरs */
#घोषणा RC32434_DDR0_ATA_BIT		5
#घोषणा RC32434_DDR0_ATA_MSK		0x000000E0
#घोषणा RC32434_DDR0_DBW_BIT		8
#घोषणा RC32434_DDR0_DBW_MSK		0x00000100
#घोषणा RC32434_DDR0_WR_BIT		9
#घोषणा RC32434_DDR0_WR_MSK		0x00000600
#घोषणा RC32434_DDR0_PS_BIT		11
#घोषणा RC32434_DDR0_PS_MSK		0x00001800
#घोषणा RC32434_DDR0_DTYPE_BIT		13
#घोषणा RC32434_DDR0_DTYPE_MSK		0x0000e000
#घोषणा RC32434_DDR0_RFC_BIT		16
#घोषणा RC32434_DDR0_RFC_MSK		0x000f0000
#घोषणा RC32434_DDR0_RP_BIT		20
#घोषणा RC32434_DDR0_RP_MSK		0x00300000
#घोषणा RC32434_DDR0_AP_BIT		22
#घोषणा RC32434_DDR0_AP_MSK		0x00400000
#घोषणा RC32434_DDR0_RCD_BIT		23
#घोषणा RC32434_DDR0_RCD_MSK		0x01800000
#घोषणा RC32434_DDR0_CL_BIT		25
#घोषणा RC32434_DDR0_CL_MSK		0x06000000
#घोषणा RC32434_DDR0_DBM_BIT		27
#घोषणा RC32434_DDR0_DBM_MSK		0x08000000
#घोषणा RC32434_DDR0_SDS_BIT		28
#घोषणा RC32434_DDR0_SDS_MSK		0x10000000
#घोषणा RC32434_DDR0_ATP_BIT		29
#घोषणा RC32434_DDR0_ATP_MSK		0x60000000
#घोषणा RC32434_DDR0_RE_BIT		31
#घोषणा RC32434_DDR0_RE_MSK		0x80000000

/* DDR bank C रेजिस्टरs */
#घोषणा RC32434_DDRC_MSK(x)		BIT_TO_MASK(x)
#घोषणा RC32434_DDRC_CES_BIT		0
#घोषणा RC32434_DDRC_ACE_BIT		1

/* Custom DDR bank रेजिस्टरs */
#घोषणा RC32434_DCST_MSK(x)		BIT_TO_MASK(x)
#घोषणा RC32434_DCST_CS_BIT		0
#घोषणा RC32434_DCST_CS_MSK		0x00000003
#घोषणा RC32434_DCST_WE_BIT		2
#घोषणा RC32434_DCST_RAS_BIT		3
#घोषणा RC32434_DCST_CAS_BIT		4
#घोषणा RC32434_DSCT_CKE_BIT		5
#घोषणा RC32434_DSCT_BA_BIT		6
#घोषणा RC32434_DSCT_BA_MSK		0x000000c0

/* DDR QSC रेजिस्टरs */
#घोषणा RC32434_QSC_DM_BIT		0
#घोषणा RC32434_QSC_DM_MSK		0x00000003
#घोषणा RC32434_QSC_DQSBS_BIT		2
#घोषणा RC32434_QSC_DQSBS_MSK		0x000000fc
#घोषणा RC32434_QSC_DB_BIT		8
#घोषणा RC32434_QSC_DB_MSK		0x00000100
#घोषणा RC32434_QSC_DBSP_BIT		9
#घोषणा RC32434_QSC_DBSP_MSK		0x01fffe00
#घोषणा RC32434_QSC_BDP_BIT		25
#घोषणा RC32434_QSC_BDP_MSK		0x7e000000

/* DDR LLC रेजिस्टरs */
#घोषणा RC32434_LLC_EAO_BIT		0
#घोषणा RC32434_LLC_EAO_MSK		0x00000001
#घोषणा RC32434_LLC_EO_BIT		1
#घोषणा RC32434_LLC_EO_MSK		0x0000003e
#घोषणा RC32434_LLC_FS_BIT		6
#घोषणा RC32434_LLC_FS_MSK		0x000000c0
#घोषणा RC32434_LLC_AS_BIT		8
#घोषणा RC32434_LLC_AS_MSK		0x00000700
#घोषणा RC32434_LLC_SP_BIT		11
#घोषणा RC32434_LLC_SP_MSK		0x001ff800

/* DDR LLFC रेजिस्टरs */
#घोषणा RC32434_LLFC_MSK(x)		BIT_TO_MASK(x)
#घोषणा RC32434_LLFC_MEN_BIT		0
#घोषणा RC32434_LLFC_EAN_BIT		1
#घोषणा RC32434_LLFC_FF_BIT		2

/* DDR DLLTA रेजिस्टरs */
#घोषणा RC32434_DLLTA_ADDR_BIT		2
#घोषणा RC32434_DLLTA_ADDR_MSK		0xfffffffc

/* DDR DLLED रेजिस्टरs */
#घोषणा RC32434_DLLED_MSK(x)		BIT_TO_MASK(x)
#घोषणा RC32434_DLLED_DBE_BIT		0
#घोषणा RC32434_DLLED_DTE_BIT		1

#पूर्ण_अगर	/* _ASM_RC32434_DDR_H_ */
