<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2010 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

#अगर_अघोषित __VISORBUS_PRIVATE_H__
#घोषणा __VISORBUS_PRIVATE_H__

#समावेश <linux/uuid.h>
#समावेश <linux/utsname.h>
#समावेश <linux/visorbus.h>

#समावेश "controlvmchannel.h"
#समावेश "vbuschannel.h"

काष्ठा visor_device *visorbus_get_device_by_id(u32 bus_no, u32 dev_no,
					       काष्ठा visor_device *from);
पूर्णांक visorbus_create_instance(काष्ठा visor_device *dev);
व्योम visorbus_हटाओ_instance(काष्ठा visor_device *bus_info);
पूर्णांक create_visor_device(काष्ठा visor_device *dev_info);
व्योम हटाओ_visor_device(काष्ठा visor_device *dev_info);
पूर्णांक visorchipset_device_छोड़ो(काष्ठा visor_device *dev_info);
पूर्णांक visorchipset_device_resume(काष्ठा visor_device *dev_info);
व्योम visorbus_response(काष्ठा visor_device *p, पूर्णांक response, पूर्णांक controlvm_id);
व्योम visorbus_device_changestate_response(काष्ठा visor_device *p, पूर्णांक response,
					  काष्ठा visor_segment_state state);
पूर्णांक visorbus_init(व्योम);
व्योम visorbus_निकास(व्योम);

/* visorchannel access functions */
काष्ठा visorchannel *visorchannel_create(u64 physaddr, gfp_t gfp,
					 स्थिर guid_t *guid, bool needs_lock);
व्योम visorchannel_destroy(काष्ठा visorchannel *channel);
पूर्णांक visorchannel_पढ़ो(काष्ठा visorchannel *channel, uदीर्घ offset,
		      व्योम *dest, uदीर्घ nbytes);
पूर्णांक visorchannel_ग_लिखो(काष्ठा visorchannel *channel, uदीर्घ offset,
		       व्योम *dest, uदीर्घ nbytes);
u64 visorchannel_get_physaddr(काष्ठा visorchannel *channel);
uदीर्घ visorchannel_get_nbytes(काष्ठा visorchannel *channel);
अक्षर *visorchannel_id(काष्ठा visorchannel *channel, अक्षर *s);
अक्षर *visorchannel_zoneid(काष्ठा visorchannel *channel, अक्षर *s);
u64 visorchannel_get_clientpartition(काष्ठा visorchannel *channel);
पूर्णांक visorchannel_set_clientpartition(काष्ठा visorchannel *channel,
				     u64 partition_handle);
अक्षर *visorchannel_guid_id(स्थिर guid_t *guid, अक्षर *s);
व्योम *visorchannel_get_header(काष्ठा visorchannel *channel);
#पूर्ण_अगर
