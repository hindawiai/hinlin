<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_TXX9_PCI_H
#घोषणा __ASM_TXX9_PCI_H

#समावेश <linux/pci.h>

बाह्य काष्ठा pci_controller txx9_primary_pcic;
काष्ठा pci_controller *
txx9_alloc_pci_controller(काष्ठा pci_controller *pcic,
			  अचिन्हित दीर्घ mem_base, अचिन्हित दीर्घ mem_size,
			  अचिन्हित दीर्घ io_base, अचिन्हित दीर्घ io_size);

पूर्णांक txx9_pci66_check(काष्ठा pci_controller *hose, पूर्णांक top_bus,
			पूर्णांक current_bus);
बाह्य पूर्णांक txx9_pci_mem_high __initdata;

बाह्य पूर्णांक txx9_pci_option;
#घोषणा TXX9_PCI_OPT_PICMG	0x0002
#घोषणा TXX9_PCI_OPT_CLK_33	0x0008
#घोषणा TXX9_PCI_OPT_CLK_66	0x0010
#घोषणा TXX9_PCI_OPT_CLK_MASK	\
	(TXX9_PCI_OPT_CLK_33 | TXX9_PCI_OPT_CLK_66)
#घोषणा TXX9_PCI_OPT_CLK_AUTO	TXX9_PCI_OPT_CLK_MASK

क्रमागत txx9_pci_err_action अणु
	TXX9_PCI_ERR_REPORT,
	TXX9_PCI_ERR_IGNORE,
	TXX9_PCI_ERR_PANIC,
पूर्ण;
बाह्य क्रमागत txx9_pci_err_action txx9_pci_err_action;

बाह्य अक्षर * (*txx9_board_pcibios_setup)(अक्षर *str);
अक्षर *txx9_pcibios_setup(अक्षर *str);

#पूर्ण_अगर /* __ASM_TXX9_PCI_H */
