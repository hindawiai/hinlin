<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित S390_CIO_IOASM_H
#घोषणा S390_CIO_IOASM_H

#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/schid.h>
#समावेश <यंत्र/crw.h>
#समावेश "orb.h"
#समावेश "cio.h"
#समावेश "trace.h"

/*
 * Some S390 specअगरic IO inकाष्ठाions
 */

पूर्णांक stsch(काष्ठा subchannel_id schid, काष्ठा schib *addr);
पूर्णांक msch(काष्ठा subchannel_id schid, काष्ठा schib *addr);
पूर्णांक tsch(काष्ठा subchannel_id schid, काष्ठा irb *addr);
पूर्णांक ssch(काष्ठा subchannel_id schid, जोड़ orb *addr);
पूर्णांक csch(काष्ठा subchannel_id schid);
पूर्णांक tpi(काष्ठा tpi_info *addr);
पूर्णांक chsc(व्योम *chsc_area);
पूर्णांक rsch(काष्ठा subchannel_id schid);
पूर्णांक hsch(काष्ठा subchannel_id schid);
पूर्णांक xsch(काष्ठा subchannel_id schid);
पूर्णांक stcrw(काष्ठा crw *crw);

#पूर्ण_अगर
