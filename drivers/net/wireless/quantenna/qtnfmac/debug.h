<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित _QTN_FMAC_DEBUG_H_
#घोषणा _QTN_FMAC_DEBUG_H_

#समावेश <linux/debugfs.h>

#समावेश "core.h"
#समावेश "bus.h"

#अगर_घोषित CONFIG_DEBUG_FS

व्योम qtnf_debugfs_init(काष्ठा qtnf_bus *bus, स्थिर अक्षर *name);
व्योम qtnf_debugfs_हटाओ(काष्ठा qtnf_bus *bus);
व्योम qtnf_debugfs_add_entry(काष्ठा qtnf_bus *bus, स्थिर अक्षर *name,
			    पूर्णांक (*fn)(काष्ठा seq_file *seq, व्योम *data));

#अन्यथा

अटल अंतरभूत व्योम qtnf_debugfs_init(काष्ठा qtnf_bus *bus, स्थिर अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत व्योम qtnf_debugfs_हटाओ(काष्ठा qtnf_bus *bus)
अणु
पूर्ण

अटल अंतरभूत व्योम
qtnf_debugfs_add_entry(काष्ठा qtnf_bus *bus, स्थिर अक्षर *name,
		       पूर्णांक (*fn)(काष्ठा seq_file *seq, व्योम *data))
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#पूर्ण_अगर /* _QTN_FMAC_DEBUG_H_ */
