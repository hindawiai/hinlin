<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * das08.h
 *
 * Header क्रम common DAS08 support (used by ISA/PCI/PCMCIA drivers)
 *
 * Copyright (C) 2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

#अगर_अघोषित _DAS08_H
#घोषणा _DAS08_H

#समावेश <linux/types.h>

काष्ठा comedi_device;

/* dअगरferent ways ai data is encoded in first two रेजिस्टरs */
क्रमागत das08_ai_encoding अणु das08_encode12, das08_encode16, das08_pcm_encode12 पूर्ण;
/* types of ai range table used by dअगरferent boards */
क्रमागत das08_lrange अणु
	das08_pg_none, das08_bipolar5, das08_pgh, das08_pgl, das08_pgm
पूर्ण;

काष्ठा das08_board_काष्ठा अणु
	स्थिर अक्षर *name;
	bool is_jr;		/* true क्रम 'JR' boards */
	अचिन्हित पूर्णांक ai_nbits;
	क्रमागत das08_lrange ai_pg;
	क्रमागत das08_ai_encoding ai_encoding;
	अचिन्हित पूर्णांक ao_nbits;
	अचिन्हित पूर्णांक di_nchan;
	अचिन्हित पूर्णांक करो_nchan;
	अचिन्हित पूर्णांक i8255_offset;
	अचिन्हित पूर्णांक i8254_offset;
	अचिन्हित पूर्णांक iosize;	/* number of ioports used */
पूर्ण;

काष्ठा das08_निजी_काष्ठा अणु
	/* bits क्रम करो/mux रेजिस्टर on boards without separate करो रेजिस्टर */
	अचिन्हित पूर्णांक करो_mux_bits;
	स्थिर अचिन्हित पूर्णांक *pg_gainlist;
पूर्ण;

पूर्णांक das08_common_attach(काष्ठा comedi_device *dev, अचिन्हित दीर्घ iobase);

#पूर्ण_अगर /* _DAS08_H */
