<शैली गुरु>
/*
 * Hardware definitions क्रम TI OMAP7XX processor.
 *
 * Cleanup क्रम Linux-2.6 by Dirk Behme <dirk.behme@de.bosch.com>
 * Adapted क्रम omap850 by Zebediah C. McClure <zmc@lurian.net>
 * Adapted क्रम omap7xx by Alistair Buxton <a.j.buxton@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __ASM_ARCH_OMAP7XX_H
#घोषणा __ASM_ARCH_OMAP7XX_H

/*
 * ----------------------------------------------------------------------------
 * Base addresses
 * ----------------------------------------------------------------------------
 */

/* Syntax: XX_BASE = Virtual base address, XX_START = Physical base address */

#घोषणा OMAP7XX_DSP_BASE	0xE0000000
#घोषणा OMAP7XX_DSP_SIZE	0x50000
#घोषणा OMAP7XX_DSP_START	0xE0000000

#घोषणा OMAP7XX_DSPREG_BASE	0xE1000000
#घोषणा OMAP7XX_DSPREG_SIZE	SZ_128K
#घोषणा OMAP7XX_DSPREG_START	0xE1000000

#घोषणा OMAP7XX_SPI1_BASE	0xfffc0800
#घोषणा OMAP7XX_SPI2_BASE	0xfffc1000

/*
 * ----------------------------------------------------------------------------
 * OMAP7XX specअगरic configuration रेजिस्टरs
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP7XX_CONFIG_BASE	0xfffe1000
#घोषणा OMAP7XX_IO_CONF_0	0xfffe1070
#घोषणा OMAP7XX_IO_CONF_1	0xfffe1074
#घोषणा OMAP7XX_IO_CONF_2	0xfffe1078
#घोषणा OMAP7XX_IO_CONF_3	0xfffe107c
#घोषणा OMAP7XX_IO_CONF_4	0xfffe1080
#घोषणा OMAP7XX_IO_CONF_5	0xfffe1084
#घोषणा OMAP7XX_IO_CONF_6	0xfffe1088
#घोषणा OMAP7XX_IO_CONF_7	0xfffe108c
#घोषणा OMAP7XX_IO_CONF_8	0xfffe1090
#घोषणा OMAP7XX_IO_CONF_9	0xfffe1094
#घोषणा OMAP7XX_IO_CONF_10	0xfffe1098
#घोषणा OMAP7XX_IO_CONF_11	0xfffe109c
#घोषणा OMAP7XX_IO_CONF_12	0xfffe10a0
#घोषणा OMAP7XX_IO_CONF_13	0xfffe10a4

#घोषणा OMAP7XX_MODE_1		0xfffe1010
#घोषणा OMAP7XX_MODE_2		0xfffe1014

/* CSMI specials: in terms of base + offset */
#घोषणा OMAP7XX_MODE2_OFFSET	0x14

/*
 * ----------------------------------------------------------------------------
 * OMAP7XX traffic controller configuration रेजिस्टरs
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP7XX_FLASH_CFG_0	0xfffecc10
#घोषणा OMAP7XX_FLASH_ACFG_0	0xfffecc50
#घोषणा OMAP7XX_FLASH_CFG_1	0xfffecc14
#घोषणा OMAP7XX_FLASH_ACFG_1	0xfffecc54

/*
 * ----------------------------------------------------------------------------
 * OMAP7XX DSP control रेजिस्टरs
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP7XX_ICR_BASE	0xfffbb800
#घोषणा OMAP7XX_DSP_M_CTL	0xfffbb804
#घोषणा OMAP7XX_DSP_MMU_BASE	0xfffed200

/*
 * ----------------------------------------------------------------------------
 * OMAP7XX PCC_UPLD configuration रेजिस्टरs
 * ----------------------------------------------------------------------------
 */
#घोषणा OMAP7XX_PCC_UPLD_CTRL_BASE	(0xfffe0900)
#घोषणा OMAP7XX_PCC_UPLD_CTRL		(OMAP7XX_PCC_UPLD_CTRL_BASE + 0x00)

#पूर्ण_अगर /*  __ASM_ARCH_OMAP7XX_H */

