<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *
 * Siano Mobile Silicon, Inc.
 * MDTV receiver kernel modules.
 * Copyright (C) 2006-2009, Uri Shkolnik
 *
 * Copyright (c) 2010 - Mauro Carvalho Chehab
 *	- Ported the driver to use rc-core
 *	- IR raw event decoding is now करोne at rc-core
 *	- Code almost re-written
 */

#अगर_अघोषित __SMS_IR_H__
#घोषणा __SMS_IR_H__

#समावेश <linux/input.h>
#समावेश <media/rc-core.h>

काष्ठा smscore_device_t;

काष्ठा ir_t अणु
	काष्ठा rc_dev *dev;
	अक्षर name[40];
	अक्षर phys[32];

	अक्षर *rc_codes;

	u32 समयout;
	u32 controller;
पूर्ण;

#अगर_घोषित CONFIG_SMS_SIANO_RC
पूर्णांक sms_ir_init(काष्ठा smscore_device_t *coredev);
व्योम sms_ir_निकास(काष्ठा smscore_device_t *coredev);
व्योम sms_ir_event(काष्ठा smscore_device_t *coredev,
			स्थिर अक्षर *buf, पूर्णांक len);
#अन्यथा
अंतरभूत अटल पूर्णांक sms_ir_init(काष्ठा smscore_device_t *coredev) अणु
	वापस 0;
पूर्ण
अंतरभूत अटल व्योम sms_ir_निकास(काष्ठा smscore_device_t *coredev) अणुपूर्ण;
अंतरभूत अटल व्योम sms_ir_event(काष्ठा smscore_device_t *coredev,
			स्थिर अक्षर *buf, पूर्णांक len) अणुपूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* __SMS_IR_H__ */

