<शैली गुरु>
/*
 *  Definitions क्रम the Watchकरोg रेजिस्टरs
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

#अगर_अघोषित __RC32434_INTEG_H__
#घोषणा __RC32434_INTEG_H__

#समावेश <यंत्र/mach-rc32434/rb.h>

#घोषणा INTEG0_BASE_ADDR	0x18030030

काष्ठा पूर्णांकeg अणु
	u32 errcs;			/* sticky use ERRCS_ */
	u32 wtcount;			/* Watchकरोg समयr count reg. */
	u32 wtcompare;			/* Watchकरोg समयr समयout value. */
	u32 wtc;			/* Watchकरोg समयr control. use WTC_ */
पूर्ण;

/* Error counters */
#घोषणा RC32434_ERR_WTO		0
#घोषणा RC32434_ERR_WNE		1
#घोषणा RC32434_ERR_UCW		2
#घोषणा RC32434_ERR_UCR		3
#घोषणा RC32434_ERR_UPW		4
#घोषणा RC32434_ERR_UPR		5
#घोषणा RC32434_ERR_UDW		6
#घोषणा RC32434_ERR_UDR		7
#घोषणा RC32434_ERR_SAE		8
#घोषणा RC32434_ERR_WRE		9

/* Watchकरोg control bits */
#घोषणा RC32434_WTC_EN		0
#घोषणा RC32434_WTC_TO		1

#पूर्ण_अगर	/* __RC32434_INTEG_H__ */
