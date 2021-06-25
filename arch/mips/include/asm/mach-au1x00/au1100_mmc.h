<शैली गुरु>
/*
 * BRIEF MODULE DESCRIPTION
 *	Defines क्रम using the MMC/SD controllers on the
 *      Alchemy Au1100 mips processor.
 *
 * Copyright (c) 2003 Embedded Edge, LLC.
 * Author: Embedded Edge, LLC.
 *         	dan@embeddededge.com or tim@embeddededge.com
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
/*
 * AU1100 MMC/SD definitions.
 *
 * From "AMD Alchemy Solutions Au1100 Processor Data Book - Preliminary"
 *    June, 2003
 */

#अगर_अघोषित __ASM_AU1100_MMC_H
#घोषणा __ASM_AU1100_MMC_H

#समावेश <linux/leds.h>

काष्ठा au1xmmc_platक्रमm_data अणु
	पूर्णांक(*cd_setup)(व्योम *mmc_host, पूर्णांक on);
	पूर्णांक(*card_inserted)(व्योम *mmc_host);
	पूर्णांक(*card_पढ़ोonly)(व्योम *mmc_host);
	व्योम(*set_घातer)(व्योम *mmc_host, पूर्णांक state);
	काष्ठा led_classdev *led;
	अचिन्हित दीर्घ mask_host_caps;
पूर्ण;

#घोषणा SD0_BASE	0xB0600000
#घोषणा SD1_BASE	0xB0680000


/*
 *  Register offsets.
 */
#घोषणा SD_TXPORT	(0x0000)
#घोषणा SD_RXPORT	(0x0004)
#घोषणा SD_CONFIG	(0x0008)
#घोषणा SD_ENABLE	(0x000C)
#घोषणा SD_CONFIG2	(0x0010)
#घोषणा SD_BLKSIZE	(0x0014)
#घोषणा SD_STATUS	(0x0018)
#घोषणा SD_DEBUG	(0x001C)
#घोषणा SD_CMD		(0x0020)
#घोषणा SD_CMDARG	(0x0024)
#घोषणा SD_RESP3	(0x0028)
#घोषणा SD_RESP2	(0x002C)
#घोषणा SD_RESP1	(0x0030)
#घोषणा SD_RESP0	(0x0034)
#घोषणा SD_TIMEOUT	(0x0038)


/*
 *  SD_TXPORT bit definitions.
 */
#घोषणा SD_TXPORT_TXD	(0x000000ff)


/*
 *  SD_RXPORT bit definitions.
 */
#घोषणा SD_RXPORT_RXD	(0x000000ff)


/*
 *  SD_CONFIG bit definitions.
 */
#घोषणा SD_CONFIG_DIV	(0x000001ff)
#घोषणा SD_CONFIG_DE	(0x00000200)
#घोषणा SD_CONFIG_NE	(0x00000400)
#घोषणा SD_CONFIG_TU	(0x00000800)
#घोषणा SD_CONFIG_TO	(0x00001000)
#घोषणा SD_CONFIG_RU	(0x00002000)
#घोषणा SD_CONFIG_RO	(0x00004000)
#घोषणा SD_CONFIG_I	(0x00008000)
#घोषणा SD_CONFIG_CR	(0x00010000)
#घोषणा SD_CONFIG_RAT	(0x00020000)
#घोषणा SD_CONFIG_DD	(0x00040000)
#घोषणा SD_CONFIG_DT	(0x00080000)
#घोषणा SD_CONFIG_SC	(0x00100000)
#घोषणा SD_CONFIG_RC	(0x00200000)
#घोषणा SD_CONFIG_WC	(0x00400000)
#घोषणा SD_CONFIG_xxx	(0x00800000)
#घोषणा SD_CONFIG_TH	(0x01000000)
#घोषणा SD_CONFIG_TE	(0x02000000)
#घोषणा SD_CONFIG_TA	(0x04000000)
#घोषणा SD_CONFIG_RH	(0x08000000)
#घोषणा SD_CONFIG_RA	(0x10000000)
#घोषणा SD_CONFIG_RF	(0x20000000)
#घोषणा SD_CONFIG_CD	(0x40000000)
#घोषणा SD_CONFIG_SI	(0x80000000)


/*
 *  SD_ENABLE bit definitions.
 */
#घोषणा SD_ENABLE_CE	(0x00000001)
#घोषणा SD_ENABLE_R	(0x00000002)


/*
 *  SD_CONFIG2 bit definitions.
 */
#घोषणा SD_CONFIG2_EN	(0x00000001)
#घोषणा SD_CONFIG2_FF	(0x00000002)
#घोषणा SD_CONFIG2_xx1	(0x00000004)
#घोषणा SD_CONFIG2_DF	(0x00000008)
#घोषणा SD_CONFIG2_DC	(0x00000010)
#घोषणा SD_CONFIG2_xx2	(0x000000e0)
#घोषणा SD_CONFIG2_BB	(0x00000080)
#घोषणा SD_CONFIG2_WB	(0x00000100)
#घोषणा SD_CONFIG2_RW	(0x00000200)
#घोषणा SD_CONFIG2_DP	(0x00000400)


/*
 *  SD_BLKSIZE bit definitions.
 */
#घोषणा SD_BLKSIZE_BS	(0x000007ff)
#घोषणा SD_BLKSIZE_BS_SHIFT	 (0)
#घोषणा SD_BLKSIZE_BC	(0x01ff0000)
#घोषणा SD_BLKSIZE_BC_SHIFT	(16)


/*
 *  SD_STATUS bit definitions.
 */
#घोषणा SD_STATUS_DCRCW (0x00000007)
#घोषणा SD_STATUS_xx1	(0x00000008)
#घोषणा SD_STATUS_CB	(0x00000010)
#घोषणा SD_STATUS_DB	(0x00000020)
#घोषणा SD_STATUS_CF	(0x00000040)
#घोषणा SD_STATUS_D3	(0x00000080)
#घोषणा SD_STATUS_xx2	(0x00000300)
#घोषणा SD_STATUS_NE	(0x00000400)
#घोषणा SD_STATUS_TU	(0x00000800)
#घोषणा SD_STATUS_TO	(0x00001000)
#घोषणा SD_STATUS_RU	(0x00002000)
#घोषणा SD_STATUS_RO	(0x00004000)
#घोषणा SD_STATUS_I	(0x00008000)
#घोषणा SD_STATUS_CR	(0x00010000)
#घोषणा SD_STATUS_RAT	(0x00020000)
#घोषणा SD_STATUS_DD	(0x00040000)
#घोषणा SD_STATUS_DT	(0x00080000)
#घोषणा SD_STATUS_SC	(0x00100000)
#घोषणा SD_STATUS_RC	(0x00200000)
#घोषणा SD_STATUS_WC	(0x00400000)
#घोषणा SD_STATUS_xx3	(0x00800000)
#घोषणा SD_STATUS_TH	(0x01000000)
#घोषणा SD_STATUS_TE	(0x02000000)
#घोषणा SD_STATUS_TA	(0x04000000)
#घोषणा SD_STATUS_RH	(0x08000000)
#घोषणा SD_STATUS_RA	(0x10000000)
#घोषणा SD_STATUS_RF	(0x20000000)
#घोषणा SD_STATUS_CD	(0x40000000)
#घोषणा SD_STATUS_SI	(0x80000000)


/*
 *  SD_CMD bit definitions.
 */
#घोषणा SD_CMD_GO	(0x00000001)
#घोषणा SD_CMD_RY	(0x00000002)
#घोषणा SD_CMD_xx1	(0x0000000c)
#घोषणा SD_CMD_CT_MASK	(0x000000f0)
#घोषणा SD_CMD_CT_0	(0x00000000)
#घोषणा SD_CMD_CT_1	(0x00000010)
#घोषणा SD_CMD_CT_2	(0x00000020)
#घोषणा SD_CMD_CT_3	(0x00000030)
#घोषणा SD_CMD_CT_4	(0x00000040)
#घोषणा SD_CMD_CT_5	(0x00000050)
#घोषणा SD_CMD_CT_6	(0x00000060)
#घोषणा SD_CMD_CT_7	(0x00000070)
#घोषणा SD_CMD_CI	(0x0000ff00)
#घोषणा SD_CMD_CI_SHIFT		(8)
#घोषणा SD_CMD_RT_MASK	(0x00ff0000)
#घोषणा SD_CMD_RT_0	(0x00000000)
#घोषणा SD_CMD_RT_1	(0x00010000)
#घोषणा SD_CMD_RT_2	(0x00020000)
#घोषणा SD_CMD_RT_3	(0x00030000)
#घोषणा SD_CMD_RT_4	(0x00040000)
#घोषणा SD_CMD_RT_5	(0x00050000)
#घोषणा SD_CMD_RT_6	(0x00060000)
#घोषणा SD_CMD_RT_1B	(0x00810000)


#पूर्ण_अगर /* __ASM_AU1100_MMC_H */
