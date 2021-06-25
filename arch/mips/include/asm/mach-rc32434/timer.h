<शैली गुरु>
/*
 *  Definitions क्रम समयr रेजिस्टरs
 *
 *  Copyright 2004 Philip Rischel <rischelp@idt.com>
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

#अगर_अघोषित __ASM_RC32434_TIMER_H
#घोषणा __ASM_RC32434_TIMER_H

#समावेश <यंत्र/mach-rc32434/rb.h>

#घोषणा TIMER0_BASE_ADDR		0x18028000
#घोषणा TIMER_COUNT			3

काष्ठा समयr_counter अणु
	u32 count;
	u32 compare;
	u32 ctc;		/*use CTC_ */
पूर्ण;

काष्ठा समयr अणु
	काष्ठा समयr_counter tim[TIMER_COUNT];
	u32 rcount;	/* use RCOUNT_ */
	u32 rcompare;	/* use RCOMPARE_ */
	u32 rtc;	/* use RTC_ */
पूर्ण;

#घोषणा RC32434_CTC_EN_BIT		0
#घोषणा RC32434_CTC_TO_BIT		1

/* Real समय घड़ी रेजिस्टरs */
#घोषणा RC32434_RTC_MSK(x)		BIT_TO_MASK(x)
#घोषणा RC32434_RTC_CE_BIT		0
#घोषणा RC32434_RTC_TO_BIT		1
#घोषणा RC32434_RTC_RQE_BIT		2

/* Counter रेजिस्टरs */
#घोषणा RC32434_RCOUNT_BIT		0
#घोषणा RC32434_RCOUNT_MSK		0x0000ffff
#घोषणा RC32434_RCOMP_BIT		0
#घोषणा RC32434_RCOMP_MSK		0x0000ffff

#पूर्ण_अगर	/* __ASM_RC32434_TIMER_H */
