<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BUG_ON_H
#घोषणा BUG_ON_H

#समावेश <निश्चित.स>

#घोषणा BUG() निश्चित(0)
#घोषणा BUG_ON(x) निश्चित(!(x))

/* Does it make sense to treat warnings as errors? */
#घोषणा WARN() BUG()
#घोषणा WARN_ON(x) (BUG_ON(x), false)

#पूर्ण_अगर
