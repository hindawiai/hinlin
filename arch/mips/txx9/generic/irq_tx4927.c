<शैली गुरु>
/*
 * Common tx4927 irq handler
 *
 * Author: MontaVista Software, Inc.
 *	   source@mvista.com
 *
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/txx9/tx4927.h>

व्योम __init tx4927_irq_init(व्योम)
अणु
	पूर्णांक i;

	mips_cpu_irq_init();
	txx9_irq_init(TX4927_IRC_REG & 0xfffffffffULL);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + TX4927_IRC_INT,
				handle_simple_irq);
	/* उठाओ priority क्रम errors, समयrs, SIO */
	txx9_irq_set_pri(TX4927_IR_ECCERR, 7);
	txx9_irq_set_pri(TX4927_IR_WTOERR, 7);
	txx9_irq_set_pri(TX4927_IR_PCIERR, 7);
	txx9_irq_set_pri(TX4927_IR_PCIPME, 7);
	क्रम (i = 0; i < TX4927_NUM_IR_TMR; i++)
		txx9_irq_set_pri(TX4927_IR_TMR(i), 6);
	क्रम (i = 0; i < TX4927_NUM_IR_SIO; i++)
		txx9_irq_set_pri(TX4927_IR_SIO(i), 5);
पूर्ण
