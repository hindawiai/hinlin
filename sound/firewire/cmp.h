<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SOUND_FIREWIRE_CMP_H_INCLUDED
#घोषणा SOUND_FIREWIRE_CMP_H_INCLUDED

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश "iso-resources.h"

काष्ठा fw_unit;

क्रमागत cmp_direction अणु
	CMP_INPUT = 0,
	CMP_OUTPUT,
पूर्ण;

/**
 * काष्ठा cmp_connection - manages an isochronous connection to a device
 * @speed: the connection's actual speed
 *
 * This काष्ठाure manages (using CMP) an isochronous stream between the local
 * computer and a device's input plug (iPCR) and output plug (oPCR).
 *
 * There is no corresponding oPCR created on the local computer, so it is not
 * possible to overlay connections on top of this one.
 */
काष्ठा cmp_connection अणु
	पूर्णांक speed;
	/* निजी: */
	bool connected;
	काष्ठा mutex mutex;
	काष्ठा fw_iso_resources resources;
	__be32 last_pcr_value;
	अचिन्हित पूर्णांक pcr_index;
	अचिन्हित पूर्णांक max_speed;
	क्रमागत cmp_direction direction;
पूर्ण;

पूर्णांक cmp_connection_init(काष्ठा cmp_connection *connection,
			काष्ठा fw_unit *unit,
			क्रमागत cmp_direction direction,
			अचिन्हित पूर्णांक pcr_index);
पूर्णांक cmp_connection_check_used(काष्ठा cmp_connection *connection, bool *used);
व्योम cmp_connection_destroy(काष्ठा cmp_connection *connection);

पूर्णांक cmp_connection_reserve(काष्ठा cmp_connection *connection,
			   अचिन्हित पूर्णांक max_payload);
व्योम cmp_connection_release(काष्ठा cmp_connection *connection);

पूर्णांक cmp_connection_establish(काष्ठा cmp_connection *connection);
पूर्णांक cmp_connection_update(काष्ठा cmp_connection *connection);
व्योम cmp_connection_अवरोध(काष्ठा cmp_connection *connection);

#पूर्ण_अगर
