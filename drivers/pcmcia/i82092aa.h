<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INCLUDE_GUARD_i82092aa_H_
#घोषणा _INCLUDE_GUARD_i82092aa_H_

#समावेश <linux/पूर्णांकerrupt.h>

/* prototypes */

अटल पूर्णांक  i82092aa_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id);
अटल व्योम i82092aa_pci_हटाओ(काष्ठा pci_dev *dev);
अटल पूर्णांक card_present(पूर्णांक socketno);
अटल irqवापस_t i82092aa_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev);




अटल पूर्णांक i82092aa_get_status(काष्ठा pcmcia_socket *socket, u_पूर्णांक *value);
अटल पूर्णांक i82092aa_set_socket(काष्ठा pcmcia_socket *socket, socket_state_t *state);
अटल पूर्णांक i82092aa_set_io_map(काष्ठा pcmcia_socket *socket, काष्ठा pccard_io_map *io);
अटल पूर्णांक i82092aa_set_mem_map(काष्ठा pcmcia_socket *socket, काष्ठा pccard_mem_map *mem);
अटल पूर्णांक i82092aa_init(काष्ठा pcmcia_socket *socket);

#पूर्ण_अगर

