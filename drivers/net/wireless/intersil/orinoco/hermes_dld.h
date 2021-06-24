<शैली गुरु>
/*
 * Copyright (C) 2007, David Kilroy
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in
 * which हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use your
 * version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */
#अगर_अघोषित _HERMES_DLD_H
#घोषणा _HERMES_DLD_H

#समावेश "hermes.h"

पूर्णांक hermesi_program_init(काष्ठा hermes *hw, u32 offset);
पूर्णांक hermesi_program_end(काष्ठा hermes *hw);
पूर्णांक hermes_program(काष्ठा hermes *hw, स्थिर अक्षर *first_block, स्थिर व्योम *end);

पूर्णांक hermes_पढ़ो_pda(काष्ठा hermes *hw,
		    __le16 *pda,
		    u32 pda_addr,
		    u16 pda_len,
		    पूर्णांक use_eeprom);
पूर्णांक hermes_apply_pda(काष्ठा hermes *hw,
		     स्थिर अक्षर *first_pdr,
		     स्थिर व्योम *pdr_end,
		     स्थिर __le16 *pda,
		     स्थिर व्योम *pda_end);
पूर्णांक hermes_apply_pda_with_शेषs(काष्ठा hermes *hw,
				   स्थिर अक्षर *first_pdr,
				   स्थिर व्योम *pdr_end,
				   स्थिर __le16 *pda,
				   स्थिर व्योम *pda_end);

माप_प्रकार hermes_blocks_length(स्थिर अक्षर *first_block, स्थिर व्योम *end);

#पूर्ण_अगर /* _HERMES_DLD_H */
