<शैली गुरु>
/*
 *  Copyright (C) 2004 Florian Schirmer <jolt@tuxbox.org>
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
 */

#समावेश <linux/init.h>
#समावेश <linux/ssb/ssb.h>
#समावेश <यंत्र/समय.स>
#समावेश <bcm47xx.h>
#समावेश <bcm47xx_board.h>

व्योम __init plat_समय_init(व्योम)
अणु
	अचिन्हित दीर्घ hz = 0;
	u16 chip_id = 0;
	अक्षर buf[10];
	पूर्णांक len;
	क्रमागत bcm47xx_board board = bcm47xx_board_get();

	/*
	 * Use deterministic values क्रम initial counter पूर्णांकerrupt
	 * so that calibrate delay aव्योमs encountering a counter wrap.
	 */
	ग_लिखो_c0_count(0);
	ग_लिखो_c0_compare(0xffff);

	चयन (bcm47xx_bus_type) अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	हाल BCM47XX_BUS_TYPE_SSB:
		hz = ssb_cpu_घड़ी(&bcm47xx_bus.ssb.mipscore) / 2;
		chip_id = bcm47xx_bus.ssb.chip_id;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	हाल BCM47XX_BUS_TYPE_BCMA:
		hz = bcma_cpu_घड़ी(&bcm47xx_bus.bcma.bus.drv_mips) / 2;
		chip_id = bcm47xx_bus.bcma.bus.chipinfo.id;
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (chip_id == 0x5354) अणु
		len = bcm47xx_nvram_दो_पर्या("clkfreq", buf, माप(buf));
		अगर (len >= 0 && !म_भेदन(buf, "200", 4))
			hz = 100000000;
	पूर्ण

	चयन (board) अणु
	हाल BCM47XX_BOARD_ASUS_WL520GC:
	हाल BCM47XX_BOARD_ASUS_WL520GU:
		hz = 100000000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!hz)
		hz = 100000000;

	/* Set MIPS counter frequency क्रम fixed_rate_समय_लोoffset() */
	mips_hpt_frequency = hz;
पूर्ण
