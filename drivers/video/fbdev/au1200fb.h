<शैली गुरु>
/*
 * BRIEF MODULE DESCRIPTION
 *	Hardware definitions क्रम the Au1200 LCD controller
 *
 * Copyright 2004 AMD
 * Author:	AMD
 *
 *  This program is मुक्त software; you can redistribute	 it and/or modअगरy it
 *  under  the terms of	 the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the	License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED	  ``AS	IS'' AND   ANY	EXPRESS OR IMPLIED
 *  WARRANTIES,	  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO	EVENT  SHALL   THE AUTHOR  BE	 LIABLE FOR ANY	  सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED	  TO, PROCUREMENT OF  SUBSTITUTE GOODS	OR SERVICES; LOSS OF
 *  USE, DATA,	OR PROFITS; OR	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN	 CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित _AU1200LCD_H
#घोषणा _AU1200LCD_H

/********************************************************************/
#घोषणा AU1200_LCD_ADDR		0xB5000000

#घोषणा uपूर्णांक8 अचिन्हित अक्षर
#घोषणा uपूर्णांक32 अचिन्हित पूर्णांक

काष्ठा au1200_lcd अणु
	अस्थिर uपूर्णांक32	reserved0;
	अस्थिर uपूर्णांक32	screen;
	अस्थिर uपूर्णांक32	backcolor;
	अस्थिर uपूर्णांक32	horztiming;
	अस्थिर uपूर्णांक32	verttiming;
	अस्थिर uपूर्णांक32	clkcontrol;
	अस्थिर uपूर्णांक32	pwmभाग;
	अस्थिर uपूर्णांक32	pwmhi;
	अस्थिर uपूर्णांक32	reserved1;
	अस्थिर uपूर्णांक32	winenable;
	अस्थिर uपूर्णांक32	colorkey;
	अस्थिर uपूर्णांक32	colorkeymsk;
	काष्ठा
	अणु
		अस्थिर uपूर्णांक32	cursorctrl;
		अस्थिर uपूर्णांक32	cursorpos;
		अस्थिर uपूर्णांक32	cursorcolor0;
		अस्थिर uपूर्णांक32	cursorcolor1;
		अस्थिर uपूर्णांक32	cursorcolor2;
		uपूर्णांक32	cursorcolor3;
	पूर्ण hwc;
	अस्थिर uपूर्णांक32	पूर्णांकstatus;
	अस्थिर uपूर्णांक32	पूर्णांकenable;
	अस्थिर uपूर्णांक32	ouपंचांगask;
	अस्थिर uपूर्णांक32	fअगरoctrl;
	uपूर्णांक32	reserved2[(0x0100-0x0058)/4];
	काष्ठा
	अणु
		अस्थिर uपूर्णांक32	winctrl0;
		अस्थिर uपूर्णांक32	winctrl1;
		अस्थिर uपूर्णांक32	winctrl2;
		अस्थिर uपूर्णांक32	winbuf0;
		अस्थिर uपूर्णांक32	winbuf1;
		अस्थिर uपूर्णांक32	winbufctrl;
		uपूर्णांक32	winreserved0;
		uपूर्णांक32	winreserved1;
	पूर्ण winकरोw[4];

	uपूर्णांक32	reserved3[(0x0400-0x0180)/4];

	अस्थिर uपूर्णांक32	palette[(0x0800-0x0400)/4];

	अस्थिर uपूर्णांक8	cursorpattern[256];
पूर्ण;

/* lcd_screen */
#घोषणा LCD_SCREEN_SEN		(1<<31)
#घोषणा LCD_SCREEN_SX		(0x07FF<<19)
#घोषणा LCD_SCREEN_SY		(0x07FF<< 8)
#घोषणा LCD_SCREEN_SWP		(1<<7)
#घोषणा LCD_SCREEN_SWD		(1<<6)
#घोषणा LCD_SCREEN_PT		(7<<0)
#घोषणा LCD_SCREEN_PT_TFT	(0<<0)
#घोषणा LCD_SCREEN_SX_N(WIDTH)	((WIDTH-1)<<19)
#घोषणा LCD_SCREEN_SY_N(HEIGHT)	((HEIGHT-1)<<8)
#घोषणा LCD_SCREEN_PT_CSTN	(1<<0)
#घोषणा LCD_SCREEN_PT_CDSTN	(2<<0)
#घोषणा LCD_SCREEN_PT_M8STN	(3<<0)
#घोषणा LCD_SCREEN_PT_M4STN	(4<<0)

/* lcd_backcolor */
#घोषणा LCD_BACKCOLOR_SBGR		(0xFF<<16)
#घोषणा LCD_BACKCOLOR_SBGG		(0xFF<<8)
#घोषणा LCD_BACKCOLOR_SBGB		(0xFF<<0)
#घोषणा LCD_BACKCOLOR_SBGR_N(N)	((N)<<16)
#घोषणा LCD_BACKCOLOR_SBGG_N(N)	((N)<<8)
#घोषणा LCD_BACKCOLOR_SBGB_N(N)	((N)<<0)

/* lcd_winenable */
#घोषणा LCD_WINENABLE_WEN3		(1<<3)
#घोषणा LCD_WINENABLE_WEN2		(1<<2)
#घोषणा LCD_WINENABLE_WEN1		(1<<1)
#घोषणा LCD_WINENABLE_WEN0		(1<<0)

/* lcd_colorkey */
#घोषणा LCD_COLORKEY_CKR		(0xFF<<16)
#घोषणा LCD_COLORKEY_CKG		(0xFF<<8)
#घोषणा LCD_COLORKEY_CKB		(0xFF<<0)
#घोषणा LCD_COLORKEY_CKR_N(N)	((N)<<16)
#घोषणा LCD_COLORKEY_CKG_N(N)	((N)<<8)
#घोषणा LCD_COLORKEY_CKB_N(N)	((N)<<0)

/* lcd_colorkeymsk */
#घोषणा LCD_COLORKEYMSK_CKMR		(0xFF<<16)
#घोषणा LCD_COLORKEYMSK_CKMG		(0xFF<<8)
#घोषणा LCD_COLORKEYMSK_CKMB		(0xFF<<0)
#घोषणा LCD_COLORKEYMSK_CKMR_N(N)	((N)<<16)
#घोषणा LCD_COLORKEYMSK_CKMG_N(N)	((N)<<8)
#घोषणा LCD_COLORKEYMSK_CKMB_N(N)	((N)<<0)

/* lcd winकरोws control 0 */
#घोषणा LCD_WINCTRL0_OX		(0x07FF<<21)
#घोषणा LCD_WINCTRL0_OY		(0x07FF<<10)
#घोषणा LCD_WINCTRL0_A		(0x00FF<<2)
#घोषणा LCD_WINCTRL0_AEN	(1<<1)
#घोषणा LCD_WINCTRL0_OX_N(N) ((N)<<21)
#घोषणा LCD_WINCTRL0_OY_N(N) ((N)<<10)
#घोषणा LCD_WINCTRL0_A_N(N) ((N)<<2)

/* lcd winकरोws control 1 */
#घोषणा LCD_WINCTRL1_PRI	(3<<30)
#घोषणा LCD_WINCTRL1_PIPE	(1<<29)
#घोषणा LCD_WINCTRL1_FRM	(0xF<<25)
#घोषणा LCD_WINCTRL1_CCO	(1<<24)
#घोषणा LCD_WINCTRL1_PO		(3<<22)
#घोषणा LCD_WINCTRL1_SZX	(0x07FF<<11)
#घोषणा LCD_WINCTRL1_SZY	(0x07FF<<0)
#घोषणा LCD_WINCTRL1_FRM_1BPP	(0<<25)
#घोषणा LCD_WINCTRL1_FRM_2BPP	(1<<25)
#घोषणा LCD_WINCTRL1_FRM_4BPP	(2<<25)
#घोषणा LCD_WINCTRL1_FRM_8BPP	(3<<25)
#घोषणा LCD_WINCTRL1_FRM_12BPP	(4<<25)
#घोषणा LCD_WINCTRL1_FRM_16BPP655	(5<<25)
#घोषणा LCD_WINCTRL1_FRM_16BPP565	(6<<25)
#घोषणा LCD_WINCTRL1_FRM_16BPP556	(7<<25)
#घोषणा LCD_WINCTRL1_FRM_16BPPI1555	(8<<25)
#घोषणा LCD_WINCTRL1_FRM_16BPPI5551	(9<<25)
#घोषणा LCD_WINCTRL1_FRM_16BPPA1555	(10<<25)
#घोषणा LCD_WINCTRL1_FRM_16BPPA5551	(11<<25)
#घोषणा LCD_WINCTRL1_FRM_24BPP		(12<<25)
#घोषणा LCD_WINCTRL1_FRM_32BPP		(13<<25)
#घोषणा LCD_WINCTRL1_PRI_N(N)	((N)<<30)
#घोषणा LCD_WINCTRL1_PO_00		(0<<22)
#घोषणा LCD_WINCTRL1_PO_01		(1<<22)
#घोषणा LCD_WINCTRL1_PO_10		(2<<22)
#घोषणा LCD_WINCTRL1_PO_11		(3<<22)
#घोषणा LCD_WINCTRL1_SZX_N(N)	((N-1)<<11)
#घोषणा LCD_WINCTRL1_SZY_N(N)	((N-1)<<0)

/* lcd winकरोws control 2 */
#घोषणा LCD_WINCTRL2_CKMODE		(3<<24)
#घोषणा LCD_WINCTRL2_DBM		(1<<23)
#घोषणा LCD_WINCTRL2_RAM		(3<<21)
#घोषणा LCD_WINCTRL2_BX			(0x1FFF<<8)
#घोषणा LCD_WINCTRL2_SCX		(0xF<<4)
#घोषणा LCD_WINCTRL2_SCY		(0xF<<0)
#घोषणा LCD_WINCTRL2_CKMODE_00		(0<<24)
#घोषणा LCD_WINCTRL2_CKMODE_01		(1<<24)
#घोषणा LCD_WINCTRL2_CKMODE_10		(2<<24)
#घोषणा LCD_WINCTRL2_CKMODE_11		(3<<24)
#घोषणा LCD_WINCTRL2_RAM_NONE		(0<<21)
#घोषणा LCD_WINCTRL2_RAM_PALETTE	(1<<21)
#घोषणा LCD_WINCTRL2_RAM_GAMMA		(2<<21)
#घोषणा LCD_WINCTRL2_RAM_BUFFER		(3<<21)
#घोषणा LCD_WINCTRL2_BX_N(N)	((N)<<8)
#घोषणा LCD_WINCTRL2_SCX_1		(0<<4)
#घोषणा LCD_WINCTRL2_SCX_2		(1<<4)
#घोषणा LCD_WINCTRL2_SCX_4		(2<<4)
#घोषणा LCD_WINCTRL2_SCY_1		(0<<0)
#घोषणा LCD_WINCTRL2_SCY_2		(1<<0)
#घोषणा LCD_WINCTRL2_SCY_4		(2<<0)

/* lcd winकरोws buffer control */
#घोषणा LCD_WINBUFCTRL_DB		(1<<1)
#घोषणा LCD_WINBUFCTRL_DBN		(1<<0)

/* lcd_पूर्णांकstatus, lcd_पूर्णांकenable */
#घोषणा LCD_INT_IFO				(0xF<<14)
#घोषणा LCD_INT_IFU				(0xF<<10)
#घोषणा LCD_INT_OFO				(1<<9)
#घोषणा LCD_INT_OFU				(1<<8)
#घोषणा LCD_INT_WAIT			(1<<3)
#घोषणा LCD_INT_SD				(1<<2)
#घोषणा LCD_INT_SA				(1<<1)
#घोषणा LCD_INT_SS				(1<<0)

/* lcd_horztiming */
#घोषणा LCD_HORZTIMING_HND2		(0x1FF<<18)
#घोषणा LCD_HORZTIMING_HND1		(0x1FF<<9)
#घोषणा LCD_HORZTIMING_HPW		(0x1FF<<0)
#घोषणा LCD_HORZTIMING_HND2_N(N)(((N)-1)<<18)
#घोषणा LCD_HORZTIMING_HND1_N(N)(((N)-1)<<9)
#घोषणा LCD_HORZTIMING_HPW_N(N)	(((N)-1)<<0)

/* lcd_verttiming */
#घोषणा LCD_VERTTIMING_VND2		(0x1FF<<18)
#घोषणा LCD_VERTTIMING_VND1		(0x1FF<<9)
#घोषणा LCD_VERTTIMING_VPW		(0x1FF<<0)
#घोषणा LCD_VERTTIMING_VND2_N(N)(((N)-1)<<18)
#घोषणा LCD_VERTTIMING_VND1_N(N)(((N)-1)<<9)
#घोषणा LCD_VERTTIMING_VPW_N(N)	(((N)-1)<<0)

/* lcd_clkcontrol */
#घोषणा LCD_CLKCONTROL_EXT		(1<<22)
#घोषणा LCD_CLKCONTROL_DELAY	(3<<20)
#घोषणा LCD_CLKCONTROL_CDD		(1<<19)
#घोषणा LCD_CLKCONTROL_IB		(1<<18)
#घोषणा LCD_CLKCONTROL_IC		(1<<17)
#घोषणा LCD_CLKCONTROL_IH		(1<<16)
#घोषणा LCD_CLKCONTROL_IV		(1<<15)
#घोषणा LCD_CLKCONTROL_BF		(0x1F<<10)
#घोषणा LCD_CLKCONTROL_PCD		(0x3FF<<0)
#घोषणा LCD_CLKCONTROL_BF_N(N)	(((N)-1)<<10)
#घोषणा LCD_CLKCONTROL_PCD_N(N)	((N)<<0)

/* lcd_pwmभाग */
#घोषणा LCD_PWMDIV_EN			(1<<31)
#घोषणा LCD_PWMDIV_PWMDIV		(0x1FFFF<<0)
#घोषणा LCD_PWMDIV_PWMDIV_N(N)	((N)<<0)

/* lcd_pwmhi */
#घोषणा LCD_PWMHI_PWMHI1		(0xFFFF<<16)
#घोषणा LCD_PWMHI_PWMHI0		(0xFFFF<<0)
#घोषणा LCD_PWMHI_PWMHI1_N(N)	((N)<<16)
#घोषणा LCD_PWMHI_PWMHI0_N(N)	((N)<<0)

/* lcd_hwccon */
#घोषणा LCD_HWCCON_EN			(1<<0)

/* lcd_cursorpos */
#घोषणा LCD_CURSORPOS_HWCXOFF		(0x1F<<27)
#घोषणा LCD_CURSORPOS_HWCXPOS		(0x07FF<<16)
#घोषणा LCD_CURSORPOS_HWCYOFF		(0x1F<<11)
#घोषणा LCD_CURSORPOS_HWCYPOS		(0x07FF<<0)
#घोषणा LCD_CURSORPOS_HWCXOFF_N(N)	((N)<<27)
#घोषणा LCD_CURSORPOS_HWCXPOS_N(N)	((N)<<16)
#घोषणा LCD_CURSORPOS_HWCYOFF_N(N)	((N)<<11)
#घोषणा LCD_CURSORPOS_HWCYPOS_N(N)	((N)<<0)

/* lcd_cursorcolor */
#घोषणा LCD_CURSORCOLOR_HWCA		(0xFF<<24)
#घोषणा LCD_CURSORCOLOR_HWCR		(0xFF<<16)
#घोषणा LCD_CURSORCOLOR_HWCG		(0xFF<<8)
#घोषणा LCD_CURSORCOLOR_HWCB		(0xFF<<0)
#घोषणा LCD_CURSORCOLOR_HWCA_N(N)	((N)<<24)
#घोषणा LCD_CURSORCOLOR_HWCR_N(N)	((N)<<16)
#घोषणा LCD_CURSORCOLOR_HWCG_N(N)	((N)<<8)
#घोषणा LCD_CURSORCOLOR_HWCB_N(N)	((N)<<0)

/* lcd_fअगरoctrl */
#घोषणा LCD_FIFOCTRL_F3IF		(1<<29)
#घोषणा LCD_FIFOCTRL_F3REQ		(0x1F<<24)
#घोषणा LCD_FIFOCTRL_F2IF		(1<<29)
#घोषणा LCD_FIFOCTRL_F2REQ		(0x1F<<16)
#घोषणा LCD_FIFOCTRL_F1IF		(1<<29)
#घोषणा LCD_FIFOCTRL_F1REQ		(0x1F<<8)
#घोषणा LCD_FIFOCTRL_F0IF		(1<<29)
#घोषणा LCD_FIFOCTRL_F0REQ		(0x1F<<0)
#घोषणा LCD_FIFOCTRL_F3REQ_N(N)	((N-1)<<24)
#घोषणा LCD_FIFOCTRL_F2REQ_N(N)	((N-1)<<16)
#घोषणा LCD_FIFOCTRL_F1REQ_N(N)	((N-1)<<8)
#घोषणा LCD_FIFOCTRL_F0REQ_N(N)	((N-1)<<0)

/* lcd_ouपंचांगask */
#घोषणा LCD_OUTMASK_MASK		(0x00FFFFFF)

/********************************************************************/
#पूर्ण_अगर /* _AU1200LCD_H */
