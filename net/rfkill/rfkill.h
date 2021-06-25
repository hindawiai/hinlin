<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007 Ivo van Doorn
 * Copyright 2009 Johannes Berg <johannes@sipsolutions.net>
 */


#अगर_अघोषित __RFKILL_INPUT_H
#घोषणा __RFKILL_INPUT_H

/* core code */
व्योम rfसमाप्त_चयन_all(स्थिर क्रमागत rfसमाप्त_type type, bool blocked);
व्योम rfसमाप्त_epo(व्योम);
व्योम rfसमाप्त_restore_states(व्योम);
व्योम rfसमाप्त_हटाओ_epo_lock(व्योम);
bool rfसमाप्त_is_epo_lock_active(व्योम);
bool rfसमाप्त_get_global_sw_state(स्थिर क्रमागत rfसमाप्त_type type);

/* input handler */
पूर्णांक rfसमाप्त_handler_init(व्योम);
व्योम rfसमाप्त_handler_निकास(व्योम);

#पूर्ण_अगर /* __RFKILL_INPUT_H */
