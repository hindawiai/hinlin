<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  ISA Plug & Play support
 *  Copyright (c) by Jaroslav Kysela <perex@suse.cz>
 */

#अगर_अघोषित LINUX_ISAPNP_H
#घोषणा LINUX_ISAPNP_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pnp.h>

/*
 *
 */

#घोषणा ISAPNP_VENDOR(a,b,c)	(((((a)-'A'+1)&0x3f)<<2)|\
				((((b)-'A'+1)&0x18)>>3)|((((b)-'A'+1)&7)<<13)|\
				((((c)-'A'+1)&0x1f)<<8))
#घोषणा ISAPNP_DEVICE(x)	((((x)&0xf000)>>8)|\
				 (((x)&0x0f00)>>8)|\
				 (((x)&0x00f0)<<8)|\
				 (((x)&0x000f)<<8))
#घोषणा ISAPNP_FUNCTION(x)	ISAPNP_DEVICE(x)

/*
 *
 */

#अगर_घोषित __KERNEL__
#समावेश <linux/mod_devicetable.h>

#घोषणा DEVICE_COUNT_COMPATIBLE 4

#घोषणा ISAPNP_CARD_DEVS	8

#घोषणा ISAPNP_CARD_ID(_va, _vb, _vc, _device) \
		.card_venकरोr = ISAPNP_VENDOR(_va, _vb, _vc), .card_device = ISAPNP_DEVICE(_device)
#घोषणा ISAPNP_CARD_END \
		.card_venकरोr = 0, .card_device = 0
#घोषणा ISAPNP_DEVICE_ID(_va, _vb, _vc, _function) \
		अणु .venकरोr = ISAPNP_VENDOR(_va, _vb, _vc), .function = ISAPNP_FUNCTION(_function) पूर्ण

काष्ठा isapnp_card_id अणु
	अचिन्हित दीर्घ driver_data;	/* data निजी to the driver */
	अचिन्हित लघु card_venकरोr, card_device;
	काष्ठा अणु
		अचिन्हित लघु venकरोr, function;
	पूर्ण devs[ISAPNP_CARD_DEVS];	/* logical devices */
पूर्ण;

#घोषणा ISAPNP_DEVICE_SINGLE(_cva, _cvb, _cvc, _cdevice, _dva, _dvb, _dvc, _dfunction) \
		.card_venकरोr = ISAPNP_VENDOR(_cva, _cvb, _cvc), .card_device =  ISAPNP_DEVICE(_cdevice), \
		.venकरोr = ISAPNP_VENDOR(_dva, _dvb, _dvc), .function = ISAPNP_FUNCTION(_dfunction)
#घोषणा ISAPNP_DEVICE_SINGLE_END \
		.card_venकरोr = 0, .card_device = 0

#अगर defined(CONFIG_ISAPNP) || (defined(CONFIG_ISAPNP_MODULE) && defined(MODULE))

#घोषणा __ISAPNP__

/* lowlevel configuration */
पूर्णांक isapnp_present(व्योम);
पूर्णांक isapnp_cfg_begin(पूर्णांक csn, पूर्णांक device);
पूर्णांक isapnp_cfg_end(व्योम);
अचिन्हित अक्षर isapnp_पढ़ो_byte(अचिन्हित अक्षर idx);
व्योम isapnp_ग_लिखो_byte(अचिन्हित अक्षर idx, अचिन्हित अक्षर val);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक isapnp_proc_init(व्योम);
पूर्णांक isapnp_proc_करोne(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक isapnp_proc_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक isapnp_proc_करोne(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* compat */
काष्ठा pnp_dev *pnp_find_dev(काष्ठा pnp_card *card,
			     अचिन्हित लघु venकरोr,
			     अचिन्हित लघु function,
			     काष्ठा pnp_dev *from);

#अन्यथा /* !CONFIG_ISAPNP */

/* lowlevel configuration */
अटल अंतरभूत पूर्णांक isapnp_present(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक isapnp_cfg_begin(पूर्णांक csn, पूर्णांक device) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक isapnp_cfg_end(व्योम) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत अचिन्हित अक्षर isapnp_पढ़ो_byte(अचिन्हित अक्षर idx) अणु वापस 0xff; पूर्ण
अटल अंतरभूत व्योम isapnp_ग_लिखो_byte(अचिन्हित अक्षर idx, अचिन्हित अक्षर val) अणु ; पूर्ण

अटल अंतरभूत काष्ठा pnp_dev *pnp_find_dev(काष्ठा pnp_card *card,
					   अचिन्हित लघु venकरोr,
					   अचिन्हित लघु function,
					   काष्ठा pnp_dev *from) अणु वापस शून्य; पूर्ण

#पूर्ण_अगर /* CONFIG_ISAPNP */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* LINUX_ISAPNP_H */
