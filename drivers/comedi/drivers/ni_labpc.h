<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Header क्रम ni_labpc ISA/PCMCIA/PCI drivers
 *
 * Copyright (C) 2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

#अगर_अघोषित _NI_LABPC_H
#घोषणा _NI_LABPC_H

क्रमागत transfer_type अणु fअगरo_not_empty_transfer, fअगरo_half_full_transfer,
	isa_dma_transfer
पूर्ण;

काष्ठा labpc_boardinfo अणु
	स्थिर अक्षर *name;
	पूर्णांक ai_speed;			/* maximum input speed in ns */
	अचिन्हित ai_scan_up:1;		/* can स्वतः scan up in ai channels */
	अचिन्हित has_ao:1;		/* has analog outमाला_दो */
	अचिन्हित is_labpc1200:1;	/* has extra regs compared to pc+ */
पूर्ण;

काष्ठा labpc_निजी अणु
	काष्ठा comedi_isadma *dma;
	काष्ठा comedi_8254 *counter;

	/*  number of data poपूर्णांकs left to be taken */
	अचिन्हित दीर्घ दीर्घ count;
	/*  software copys of bits written to command रेजिस्टरs */
	अचिन्हित पूर्णांक cmd1;
	अचिन्हित पूर्णांक cmd2;
	अचिन्हित पूर्णांक cmd3;
	अचिन्हित पूर्णांक cmd4;
	अचिन्हित पूर्णांक cmd5;
	अचिन्हित पूर्णांक cmd6;
	/*  store last पढ़ो of board status रेजिस्टरs */
	अचिन्हित पूर्णांक stat1;
	अचिन्हित पूर्णांक stat2;

	/* we are using dma/fअगरo-half-full/etc. */
	क्रमागत transfer_type current_transfer;
	/*
	 * function poपूर्णांकers so we can use inb/outb or पढ़ोb/ग_लिखोb as
	 * appropriate
	 */
	अचिन्हित पूर्णांक (*पढ़ो_byte)(काष्ठा comedi_device *dev, अचिन्हित दीर्घ reg);
	व्योम (*ग_लिखो_byte)(काष्ठा comedi_device *dev,
			   अचिन्हित पूर्णांक byte, अचिन्हित दीर्घ reg);
पूर्ण;

पूर्णांक labpc_common_attach(काष्ठा comedi_device *dev,
			अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ isr_flags);
व्योम labpc_common_detach(काष्ठा comedi_device *dev);

#पूर्ण_अगर /* _NI_LABPC_H */
