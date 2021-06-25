<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mediabay.h: definitions क्रम using the media bay
 * on PowerBook 3400 and similar computers.
 *
 * Copyright (C) 1997 Paul Mackerras.
 */
#अगर_अघोषित _PPC_MEDIABAY_H
#घोषणा _PPC_MEDIABAY_H

#अगर_घोषित __KERNEL__

#घोषणा MB_FD		0	/* media bay contains floppy drive (स्वतःmatic eject ?) */
#घोषणा MB_FD1		1	/* media bay contains floppy drive (manual eject ?) */
#घोषणा MB_SOUND	2	/* sound device ? */
#घोषणा MB_CD		3	/* media bay contains ATA drive such as CD or ZIP */
#घोषणा MB_PCI		5	/* media bay contains a PCI device */
#घोषणा MB_POWER	6	/* media bay contains a Power device (???) */
#घोषणा MB_NO		7	/* media bay contains nothing */

काष्ठा macio_dev;

#अगर_घोषित CONFIG_PMAC_MEDIABAY

/* Check the content type of the bay, वापसs MB_NO अगर the bay is still
 * transitionning
 */
बाह्य पूर्णांक check_media_bay(काष्ठा macio_dev *bay);

/* The ATA driver uses the calls below to temporarily hold on the
 * media bay callbacks जबतक initializing the पूर्णांकerface
 */
बाह्य व्योम lock_media_bay(काष्ठा macio_dev *bay);
बाह्य व्योम unlock_media_bay(काष्ठा macio_dev *bay);

#अन्यथा

अटल अंतरभूत पूर्णांक check_media_bay(काष्ठा macio_dev *bay)
अणु
	वापस MB_NO;
पूर्ण

अटल अंतरभूत व्योम lock_media_bay(काष्ठा macio_dev *bay) अणु पूर्ण
अटल अंतरभूत व्योम unlock_media_bay(काष्ठा macio_dev *bay) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _PPC_MEDIABAY_H */
