<शैली गुरु>
/*
 *  BRIEF MODULE DESCRIPTION
 *     pci_ops क्रम IDT EB434 board
 *
 *  Copyright 2004 IDT Inc. (rischelp@idt.com)
 *  Copyright 2006 Felix Fietkau <nbd@खोलोwrt.org>
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
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mach-rc32434/rc32434.h>
#समावेश <यंत्र/mach-rc32434/pci.h>

#घोषणा PCI_ACCESS_READ	 0
#घोषणा PCI_ACCESS_WRITE 1


#घोषणा PCI_CFG_SET(bus, slot, func, off) \
	(rc32434_pci->pcicfga = (0x80000000 | \
				((bus) << 16) | ((slot)<<11) | \
				((func)<<8) | (off)))

अटल अंतरभूत पूर्णांक config_access(अचिन्हित अक्षर access_type,
				काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				अचिन्हित अक्षर where, u32 *data)
अणु
	अचिन्हित पूर्णांक slot = PCI_SLOT(devfn);
	u8 func = PCI_FUNC(devfn);

	/* Setup address */
	PCI_CFG_SET(bus->number, slot, func, where);
	rc32434_sync();

	अगर (access_type == PCI_ACCESS_WRITE)
		rc32434_pci->pcicfgd = *data;
	अन्यथा
		*data = rc32434_pci->pcicfgd;

	rc32434_sync();

	वापस 0;
पूर्ण


/*
 * We can't address 8 and 16 bit words directly.  Instead we have to
 * पढ़ो/ग_लिखो a 32bit word and mask/modअगरy the data we actually want.
 */
अटल पूर्णांक पढ़ो_config_byte(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, u8 *val)
अणु
	u32 data;
	पूर्णांक ret;

	ret = config_access(PCI_ACCESS_READ, bus, devfn, where, &data);
	*val = (data >> ((where & 3) << 3)) & 0xff;
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_config_word(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, u16 *val)
अणु
	u32 data;
	पूर्णांक ret;

	ret = config_access(PCI_ACCESS_READ, bus, devfn, where, &data);
	*val = (data >> ((where & 3) << 3)) & 0xffff;
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_config_dword(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, u32 *val)
अणु
	पूर्णांक ret;
	पूर्णांक delay = 1;

	/*
	 * Don't scan too far, अन्यथा there will be errors with plugged in
	 * daughterboard (rb564).
	 */
	अगर (bus->number == 0 && PCI_SLOT(devfn) > 21)
		वापस 0;

retry:
	ret = config_access(PCI_ACCESS_READ, bus, devfn, where, val);

	/*
	 * Certain devices react delayed at device scan समय, this
	 * gives them समय to settle
	 */
	अगर (where == PCI_VENDOR_ID) अणु
		अगर (ret == 0xffffffff || ret == 0x00000000 ||
		    ret == 0x0000ffff || ret == 0xffff0000) अणु
			अगर (delay > 4)
				वापस 0;
			delay *= 2;
			msleep(delay);
			जाओ retry;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
ग_लिखो_config_byte(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		  u8 val)
अणु
	u32 data = 0;

	अगर (config_access(PCI_ACCESS_READ, bus, devfn, where, &data))
		वापस -1;

	data = (data & ~(0xff << ((where & 3) << 3))) |
	    (val << ((where & 3) << 3));

	अगर (config_access(PCI_ACCESS_WRITE, bus, devfn, where, &data))
		वापस -1;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण


अटल पूर्णांक
ग_लिखो_config_word(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		  u16 val)
अणु
	u32 data = 0;

	अगर (config_access(PCI_ACCESS_READ, bus, devfn, where, &data))
		वापस -1;

	data = (data & ~(0xffff << ((where & 3) << 3))) |
	    (val << ((where & 3) << 3));

	अगर (config_access(PCI_ACCESS_WRITE, bus, devfn, where, &data))
		वापस -1;


	वापस PCIBIOS_SUCCESSFUL;
पूर्ण


अटल पूर्णांक
ग_लिखो_config_dword(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		   u32 val)
अणु
	अगर (config_access(PCI_ACCESS_WRITE, bus, devfn, where, &val))
		वापस -1;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक pci_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	चयन (size) अणु
	हाल 1:
		वापस पढ़ो_config_byte(bus, devfn, where, (u8 *) val);
	हाल 2:
		वापस पढ़ो_config_word(bus, devfn, where, (u16 *) val);
	शेष:
		वापस पढ़ो_config_dword(bus, devfn, where, val);
	पूर्ण
पूर्ण

अटल पूर्णांक pci_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, पूर्णांक size, u32 val)
अणु
	चयन (size) अणु
	हाल 1:
		वापस ग_लिखो_config_byte(bus, devfn, where, (u8) val);
	हाल 2:
		वापस ग_लिखो_config_word(bus, devfn, where, (u16) val);
	शेष:
		वापस ग_लिखो_config_dword(bus, devfn, where, val);
	पूर्ण
पूर्ण

काष्ठा pci_ops rc32434_pci_ops = अणु
	.पढ़ो = pci_config_पढ़ो,
	.ग_लिखो = pci_config_ग_लिखो,
पूर्ण;
