<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Linaro Ltd.
 */
#अगर_अघोषित __VENUS_FIRMWARE_H__
#घोषणा __VENUS_FIRMWARE_H__

काष्ठा device;

पूर्णांक venus_firmware_init(काष्ठा venus_core *core);
व्योम venus_firmware_deinit(काष्ठा venus_core *core);
पूर्णांक venus_boot(काष्ठा venus_core *core);
पूर्णांक venus_shutकरोwn(काष्ठा venus_core *core);
पूर्णांक venus_set_hw_state(काष्ठा venus_core *core, bool suspend);

अटल अंतरभूत पूर्णांक venus_set_hw_state_suspend(काष्ठा venus_core *core)
अणु
	वापस venus_set_hw_state(core, false);
पूर्ण

अटल अंतरभूत पूर्णांक venus_set_hw_state_resume(काष्ठा venus_core *core)
अणु
	वापस venus_set_hw_state(core, true);
पूर्ण

#पूर्ण_अगर
