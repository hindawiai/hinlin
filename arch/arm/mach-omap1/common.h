<शैली गुरु>
/*
 *
 * Header क्रम code common to all OMAP1 machines.
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

#अगर_अघोषित __ARCH_ARM_MACH_OMAP1_COMMON_H
#घोषणा __ARCH_ARM_MACH_OMAP1_COMMON_H

#समावेश <linux/platक्रमm_data/i2c-omap.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/exception.h>

#समावेश <mach/irqs.h>

#समावेश "soc.h"
#समावेश "i2c.h"

#अगर defined(CONFIG_ARCH_OMAP730) || defined(CONFIG_ARCH_OMAP850)
व्योम omap7xx_map_io(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap7xx_map_io(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP15XX
व्योम omap1510_fpga_init_irq(व्योम);
व्योम omap15xx_map_io(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap1510_fpga_init_irq(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम omap15xx_map_io(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP16XX
व्योम omap16xx_map_io(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap16xx_map_io(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OMAP_SERIAL_WAKE
पूर्णांक omap_serial_wakeup_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap_serial_wakeup_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम omap1_init_early(व्योम);
व्योम omap1_init_irq(व्योम);
व्योम __exception_irq_entry omap1_handle_irq(काष्ठा pt_regs *regs);
व्योम omap1_init_late(व्योम);
व्योम omap1_restart(क्रमागत reboot_mode, स्थिर अक्षर *);

बाह्य व्योम __init omap_check_revision(व्योम);

काष्ठा nand_chip;
बाह्य व्योम omap1_nand_cmd_ctl(काष्ठा nand_chip *this, पूर्णांक cmd,
			       अचिन्हित पूर्णांक ctrl);

बाह्य व्योम omap1_समयr_init(व्योम);
#अगर_घोषित CONFIG_OMAP_32K_TIMER
बाह्य पूर्णांक omap_32k_समयr_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक __init omap_32k_समयr_init(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP16XX
बाह्य पूर्णांक ocpi_enable(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ocpi_enable(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

बाह्य u32 omap1_get_reset_sources(व्योम);

#पूर्ण_अगर /* __ARCH_ARM_MACH_OMAP1_COMMON_H */
