<शैली गुरु>
/*
 * Handling of a sram zone क्रम bestcomm
 *
 *
 * Copyright (C) 2007 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __BESTCOMM_SRAM_H__
#घोषणा __BESTCOMM_SRAM_H__

#समावेश <यंत्र/rheap.h>
#समावेश <यंत्र/mmu.h>
#समावेश <linux/spinlock.h>


/* Structure used पूर्णांकernally */
	/* The पूर्णांकernals are here क्रम the अंतरभूत functions
	 * sake, certainly not क्रम the user to mess with !
	 */
काष्ठा bcom_sram अणु
	phys_addr_t		 base_phys;
	व्योम 			*base_virt;
	अचिन्हित पूर्णांक		 size;
	rh_info_t		*rh;
	spinlock_t		 lock;
पूर्ण;

बाह्य काष्ठा bcom_sram *bcom_sram;


/* Public API */
बाह्य पूर्णांक  bcom_sram_init(काष्ठा device_node *sram_node, अक्षर *owner);
बाह्य व्योम bcom_sram_cleanup(व्योम);

बाह्य व्योम* bcom_sram_alloc(पूर्णांक size, पूर्णांक align, phys_addr_t *phys);
बाह्य व्योम  bcom_sram_मुक्त(व्योम *ptr);

अटल अंतरभूत phys_addr_t bcom_sram_va2pa(व्योम *va) अणु
	वापस bcom_sram->base_phys +
		(अचिन्हित दीर्घ)(va - bcom_sram->base_virt);
पूर्ण

अटल अंतरभूत व्योम *bcom_sram_pa2va(phys_addr_t pa) अणु
	वापस bcom_sram->base_virt +
		(अचिन्हित दीर्घ)(pa - bcom_sram->base_phys);
पूर्ण


#पूर्ण_अगर  /* __BESTCOMM_SRAM_H__ */

