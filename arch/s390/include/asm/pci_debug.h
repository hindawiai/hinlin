<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _S390_ASM_PCI_DEBUG_H
#घोषणा _S390_ASM_PCI_DEBUG_H

#समावेश <यंत्र/debug.h>

बाह्य debug_info_t *pci_debug_msg_id;
बाह्य debug_info_t *pci_debug_err_id;

#घोषणा zpci_dbg(imp, fmt, args...)				\
	debug_प्र_लिखो_event(pci_debug_msg_id, imp, fmt, ##args)

#घोषणा zpci_err(text...)							\
	करो अणु									\
		अक्षर debug_buffer[16];						\
		snम_लिखो(debug_buffer, 16, text);				\
		debug_text_event(pci_debug_err_id, 0, debug_buffer);		\
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम zpci_err_hex(व्योम *addr, पूर्णांक len)
अणु
	debug_event(pci_debug_err_id, 0, addr, len);
पूर्ण

#पूर्ण_अगर
