<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*** -*- linux-c -*- **********************************************************

     Driver क्रम Aपंचांगel at76c502 at76c504 and at76c506 wireless cards.

         Copyright 2005 Dan Williams and Red Hat, Inc.


******************************************************************************/

#अगर_अघोषित _ATMEL_H
#घोषणा _ATMEL_H

प्रकार क्रमागत अणु
	ATMEL_FW_TYPE_NONE = 0,
	ATMEL_FW_TYPE_502,
	ATMEL_FW_TYPE_502D,
	ATMEL_FW_TYPE_502E,
	ATMEL_FW_TYPE_502_3COM,
	ATMEL_FW_TYPE_504,
	ATMEL_FW_TYPE_504_2958,
	ATMEL_FW_TYPE_504A_2958,
	ATMEL_FW_TYPE_506
पूर्ण AपंचांगelFWType;

काष्ठा net_device *init_aपंचांगel_card(अचिन्हित लघु, अचिन्हित दीर्घ, स्थिर AपंचांगelFWType, काष्ठा device *, 
				    पूर्णांक (*present_func)(व्योम *), व्योम * );
व्योम stop_aपंचांगel_card( काष्ठा net_device *);
पूर्णांक aपंचांगel_खोलो( काष्ठा net_device * );

#पूर्ण_अगर
