<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**
 * file phonet.h
 *
 * Phonet sockets kernel पूर्णांकerface
 *
 * Copyright (C) 2008 Nokia Corporation. All rights reserved.
 */
#अगर_अघोषित LINUX_PHONET_H
#घोषणा LINUX_PHONET_H

#समावेश <uapi/linux/phonet.h>

#घोषणा SIOCPNGAUTOCONF		(SIOCDEVPRIVATE + 0)

काष्ठा अगर_phonet_स्वतःconf अणु
	uपूर्णांक8_t device;
पूर्ण;

काष्ठा अगर_phonet_req अणु
	अक्षर अगरr_phonet_name[16];
	जोड़ अणु
		काष्ठा अगर_phonet_स्वतःconf अगरru_phonet_स्वतःconf;
	पूर्ण अगरr_अगरru;
पूर्ण;
#घोषणा अगरr_phonet_स्वतःconf अगरr_अगरru.अगरru_phonet_स्वतःconf
#पूर्ण_अगर
